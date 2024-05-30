#include "../public/Player.h"
Player::Player(int ID, std::string Name, std::string Rank, int Age, Phone* phone, Computer* computer, BankAccount* bank_account, bool bCanBeTargeted, EFactions faction, int reputationRebel, int reputationCorpo) : Person(ID, Name, Rank, Age, phone, computer, bank_account, bCanBeTargeted, faction)
{
    this->ID = ID;
    this->Name = Name;
    this->Rank = Rank;
    this->Age = Age;
    this->PersonPhone = phone;
    this->PersonComputer = computer;
    this->PersonBankAccount = bank_account;
    this->bCanBeTargeted = bCanBeTargeted;
    this->faction = faction;
    this->reputationRebel = reputationRebel;
    this->reputationCorpo = reputationCorpo;
}
Player::~Player() { }

int Player::GetReputationRebel() const
{
    return reputationRebel;
}
void Player::SetReputationRebel(const int reputationRebel)
{
    this->reputationRebel = reputationRebel;
}
int Player::GetReputationCorpo() const
{
    return reputationCorpo;
}
void Player::SetReputationCorpo(int reputationCorpo)
{
    this->reputationCorpo = reputationCorpo;
}

int Player::GetDialogueID() const
{
    return CurrentDialogueID;
}

void Player::MoveDialogueID()
{
    CurrentDialogueID++;
}

void Player::ResetDialogueID()
{
    CurrentDialogueID = -1;
}

void Player::SetCalledPerson(Person* newPerson)
{
    CalledPerson = newPerson;
}

void Player::NullCalledPerson()
{
    CalledPerson = nullptr;
}

Person* Player::GetCalledPerson()
{
    return CalledPerson;
}

std::string Player::GetCurrentIP()
{
    return CurrentIP;
}

void Player::SetCurrentIP(std::string newIP)
{
    std::cout << "Currently connected to " << newIP << std::endl;
    this->CurrentIP = newIP;
}

// debug
// todo: remove
void Player::PrintPlayer() const
{
    std::cout << std::endl << "PLAYER DATA" << std::endl;
    std::cout << "ID " << ID << std::endl;
    std::cout << "Name " << Name << std::endl;
    std::cout << "Rank " << Rank << std::endl;
    std::cout << "Age " << Age << std::endl;
    std::cout << "Phone number " << PersonPhone->GetNumber() << std::endl;
    std::cout << "IP address " << PersonComputer->GetIP() << std::endl;
    std::cout << "Money on account " << PersonBankAccount->GetMoney() << std::endl;
    std::cout << "Can be contract target " << bCanBeTargeted << std::endl;
    std::cout << "Rebel reputation " << reputationRebel << std::endl;
    std::cout << "Corpo reputation " << reputationCorpo << std::endl;
}
