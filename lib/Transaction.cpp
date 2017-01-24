#include <string>
#include <list>
#include "Posting.cpp"

struct Transaction {
    int id;
    std::string state;
    std::string date;
    std::string payee;
    std::string note;
    std::list<Posting> postings;

    /**
     * Sort by debet first, credit last
     */
    void sortPostings()
    {
        this->postings.sort([](const Posting &a, const Posting &b) {
            return a.amount > b.amount;
        });
    }


    std::string toLatex(std::list<DictionaryEntry> &dictionary)
    {
        std::string transactionRow;
        // Id
        std::string idStringified = std::to_string(this->id);
        transactionRow += std::string(5 - idStringified.length(), '0').append(idStringified) + " & ";
        // Date
        transactionRow += this->date + " & ";
        // AccountCode
        transactionRow += " & ";
        // Payee
        transactionRow += "\\textbf{" + this->payee + "} & ";
        // Debit
        transactionRow += " & ";
        // Credit
        transactionRow += "\\\\";
        transactionRow += "\n";

        if (this->note.length()) {
            // Id
            transactionRow += " & ";
            // Date
            transactionRow += " & ";
            // AccountCode
            transactionRow += " & ";
            // Payee
            transactionRow += "\\emph{" + this->note + "} & ";
            // Debit
            transactionRow += " & ";
            // Credit
            transactionRow += "\\\\";
            transactionRow += "\n";
        }

        this->sortPostings();
        for (std::list<Posting>::iterator posting = this->postings.begin();
             posting != this->postings.end();
             ++posting) {
            transactionRow += (*posting).toLatex(dictionary);
        }

        transactionRow += "\\hline";

        return transactionRow;
    }
};
