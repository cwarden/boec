#include <iostream>
#include <vector>
#include <list>

#include "vendor/rapidxml/rapidxml.hpp"
#include "Transaction.cpp"


int main()
{

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

    std::list<Transaction> parsedTransactions;
    rapidxml::xml_node<>* currentTransaction = transactions->first_node();

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
        transaction->payee = currentTransaction->first_node("payee")->value();
        transaction->date = currentTransaction->first_node("date")->value();
        transaction->state = currentTransaction->first_node("date")->value();


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
        }

        parsedTransactions.push_back(*transaction);

        std::cout << transaction->toLatex();
        std::cout << "\n";

        currentTransaction = currentTransaction->next_sibling();
    }

    return 0;
}
