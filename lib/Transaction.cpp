#include <string>
#include <list>
#include "Posting.cpp"

struct Transaction {
    std::string state;
    std::string date;
    std::string payee;
    std::string note;
    std::list<Posting> postings;

    std::string toString()
    {
        return this->payee + this->date;
    }

    std::string toLatex(std::list<DictionaryEntry> &dictionary)
    {
        std::string transactionRow;
        // Date
        transactionRow += this->date + " & ";
        // AccountCode
        transactionRow += " & ";
        // Payee
        transactionRow += this->payee + " & ";
        // Debit
        transactionRow += " & ";
        // Credit
        transactionRow += "\\\\";
        transactionRow += "\n";

        for (std::list<Posting>::iterator posting = this->postings.begin();
             posting != this->postings.end();
             ++posting) {
            transactionRow += (*posting).toLatex(dictionary);
        }

        transactionRow += "\\hline";

        return transactionRow;
    }
};
