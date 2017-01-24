#include <iostream>
#include <vector>
#include <list>
#include <fstream>

#include "vendor/rapidxml/rapidxml.hpp"
#include "lib/Transaction.cpp"
#include "lib/Dictionary.cpp"

int main(int argc, char* argv[])
{

    /**
     * Check if we have an account dictionary.
     * If so, read it. If not, issue a warning.
     */

    std::list<DictionaryEntry> dictionary;

    std::ifstream in_stream;
    in_stream.open((std::string) (getenv("HOME")) + "/.boecdict");
    if (in_stream.fail()) {
        std::cerr << "Not using account codes, could not read " << getenv("HOME") << "/.boecdict\n";
    } else {
        // TODO: Move arg parsing to a centralized place so we don't repeat
        // ourselves when checking for the --template flag.
        int codeLength = 9;
        for (int i = 1; i < argc; ++i) {
            if (std::string(argv[i]) == "--codelength") {
                if (i + 1 < argc) {
                    codeLength = std::stoi(argv[i+1]);
                } else {
                    std::cerr << "Sorry, the --codelength flag expects a value greater than zero." << std::endl;
                    return 1;
                }
            }
        }
        while(!in_stream.eof()) {
            std::string line;
            getline(in_stream, line);
            if (!line.size() || line.substr(0,2) == "//") {
                continue;
            }
            auto entry = new DictionaryEntry {line.substr(0, codeLength), line.substr(codeLength + 1, line.size())};
            dictionary.push_back(*entry);
            delete entry;
        }
    }



    /**
     * Create the document from stdin
     */

    std::string input_xml;
    std::string line;

    while (getline(std::cin, line)) {
        input_xml += line;
    }


    /**
     * Parse the input as XML.
     */

    rapidxml::xml_document<> doc;
    std::vector<char> xml_copy(input_xml.begin(), input_xml.end());

    xml_copy.push_back('\0');
    doc.parse<0>(&xml_copy[0]);


    /**
     * Iterate over our XML DOM.
     */

    rapidxml::xml_node<>* ledger = doc.first_node("ledger");
    rapidxml::xml_node<>* accounts = ledger->first_node("accounts");
    rapidxml::xml_node<>* transactions = ledger->first_node("transactions");


    /**
     * Read each transaction into a Transaction struct.
     */

    std::string outputBuffer = "";
    rapidxml::xml_node<>* currentTransaction = transactions->first_node();

    int transactionId = 1;
    while(currentTransaction != nullptr) {

        /**
         * Check the state of our transaction. For reporting, we'll only use
         * transactions that *have* a (or any) state.
         */

        if (!currentTransaction->first_attribute("state")) {
            currentTransaction = currentTransaction->next_sibling();
            continue;
        }

        auto transaction = new Transaction;
        transaction->id = transactionId;
        transaction->payee = currentTransaction->first_node("payee")->value();
        transaction->date = currentTransaction->first_node("date")->value();
        transaction->state = currentTransaction->first_node("date")->value();
        transaction->note = currentTransaction->first_node("note") ? currentTransaction->first_node("note")->value() : "";


        /**
         * Add the postings to the transaction.
         */

        rapidxml::xml_node<>* currentPosting = currentTransaction->first_node("postings")
                                               ->first_node("posting");

        while (currentPosting != nullptr) {
            auto posting = new Posting;
            posting->accountName = currentPosting->first_node("account")
                                   ->first_node("name")
                                   ->value();
            posting->amount = std::stof(currentPosting->first_node("post-amount")
                                        ->first_node("amount")
                                        ->first_node("quantity")
                                        ->value());
            transaction->postings.push_back(*posting);
            currentPosting = currentPosting->next_sibling();
            delete posting;
        }

        outputBuffer += transaction->toLatex(dictionary) + "\n";
        delete transaction;

        currentTransaction = currentTransaction->next_sibling();
        transactionId++;
    }

    std::string templatePath;
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--template") {
            if (i + 1 < argc) {
                templatePath = argv[i+1];
                std::ifstream templateFile;
                templateFile.open(templatePath);
                if (templateFile.fail()) {
                    std::cerr << "Sorry, the template \"" + templatePath + "\" could not be read." << std::endl;
                    return 1;
                }

                while(!templateFile.eof()) {
                    std::string templateLine;
                    getline(templateFile, templateLine);
                    if (templateLine.find("\\input{__BOEC__}") != std::string::npos) {
                        std::cout << outputBuffer;
                        continue;
                    } else {
                        std::cout << templateLine << std::endl;
                        continue;
                    }
                }

                return 0;
            } else {
                std::cerr << "Sorry, the --template option expects a path to a .tex file." << std::endl;
                return 1;
            }
        }
    }

    std::cout << outputBuffer;

    return 0;
}
