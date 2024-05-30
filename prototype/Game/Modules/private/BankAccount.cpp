#include "../public/WIP - BankAccount.h"
BankAccount::BankAccount(int accountID, int money)
{
    this->accountID = accountID;
    this->money = money;
}

int BankAccount::GetAccountID() const
{
    return accountID;
}

void BankAccount::SetAccountID(int newAccountID)
{
    this->accountID = newAccountID;
}

int BankAccount::GetMoney() const
{
    return money;
}

void BankAccount::SetMoney(int newMoney)
{
    this->money = newMoney;
}
