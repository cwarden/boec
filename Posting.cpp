struct Posting
{
    std::string accountName;
    bool isDebit;
    float amount;

    std::string toString()
    {
        std::string postingRow;
        postingRow += " & "; // date
        postingRow += this->accountName;
        postingRow += " & "; // payee
        postingRow += std::to_string(this->amount);
        return postingRow;
    }
};
