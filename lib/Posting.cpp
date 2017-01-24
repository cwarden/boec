#include <cmath>
#include "Dictionary.cpp"

struct Posting {

    std::string accountName;
    float amount;
    std::string accountCode;

    std::string toLatex(std::list<DictionaryEntry> &dictionary)
    {

        std::string postingRow;
        char printableAmount[20];
        snprintf(printableAmount, 100, "%.2f", std::fabs(this->amount));

        for(std::list<DictionaryEntry>::iterator dictionaryEntry = dictionary.begin();
            dictionaryEntry != dictionary.end();
            ++dictionaryEntry) {
            if (this->accountName.compare(dictionaryEntry->description) == 0) {
                this->accountCode = dictionaryEntry->code;
                break;
            }
        }

        // ID
        postingRow += " & ";

        // Date
        postingRow += " & ";

        // Debit
        postingRow += this->accountCode.size() ? this->accountCode : "";
        postingRow += " & ";

        // Payee
        postingRow += this->accountName + " & ";

        // Debit
        postingRow += (this->amount > 0) ? printableAmount : "";
        postingRow += " & ";

        // Credit
        postingRow += (this->amount < 0) ? printableAmount : "";

        postingRow += "\\\\";
        postingRow += "\n";
        return postingRow;
    }
};
