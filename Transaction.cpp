#include <string>
#include <list>
#include "Posting.cpp"

struct Transaction
{
    std::string state;
    std::string date;
    std::string payee;
    std::list<Posting> postings;

    std::string toString()
    {
        return this->payee + this->date;
    }

    std::string toLatex()
    {
        std::string transactionRow;
        transactionRow += this->date + " & ";
        transactionRow += " & "; // D account
        transactionRow += " & "; // C account
        transactionRow += this->payee + " & ";
        transactionRow += "\\\\";

        /**
         * Iterate through all postings.
         */

        for (std::list<Posting>::iterator it = this->postings.begin(); it != this->postings.end(); ++it) {
            std::cout << (*it).toString();
        }

        return transactionRow;
    }
};
