#include <cmath>
#include <sstream>
#include "Dictionary.cpp"

struct Posting {

    std::string accountName;
    float amount;
    std::string accountCode;
    std::string commodity;

    std::string toLatex(std::list<DictionaryEntry> &dictionary)
    {

        std::string postingRow;
        char printableAmount[10];
        if (this->commodity.size()) {
            snprintf(printableAmount, 10, "%g", std::fabs(this->amount));
        } else {
            snprintf(printableAmount, 10, "%.2f", std::fabs(this->amount));
        }

        std::ostringstream s;
        s << printableAmount;
        if (this->commodity.size()) {
            s << " " << this->commodity;
        }
        std::string outputAmount = s.str();

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

        // Payee
        postingRow += this->accountName + " & ";

        // Debit
        postingRow += (this->amount > 0) ? outputAmount : "";
        postingRow += " & ";

        // Credit
        postingRow += (this->amount < 0) ? outputAmount : "";

        postingRow += "\\\\";
        postingRow += "\n";
        return postingRow;
    }
};
