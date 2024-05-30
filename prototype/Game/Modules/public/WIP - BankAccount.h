#pragma once
// non operational
// probably will be scrapped

class BankAccount
{
public:
    BankAccount(int accountID, int money);
    int GetAccountID() const;
    void SetAccountID(int newAccountID);
    int GetMoney() const;
    void SetMoney(int newMoney);
    
private:
    int accountID;
    int money;
};
