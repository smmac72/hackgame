#pragma once

#include "Person.h"

class Player : public Person
{
public:
    Player(int ID, std::string Name, std::string Rank, int Age, Phone* phone, Computer* computer, BankAccount* bank_account, bool bCanBeTargeted, EFactions faction, int reputationRebel, int reputationCorpo);
    ~Player();

    void PrintPlayer() const;

    int GetReputationRebel() const;
    void SetReputationRebel(int reputationRebel);
    int GetReputationCorpo() const;
    void SetReputationCorpo(int reputationCorpo);

    int GetDialogueID() const;
    void MoveDialogueID();
    void ResetDialogueID();
    void SetCalledPerson(Person* newPerson);
    void NullCalledPerson();
    Person* GetCalledPerson();

    std::string GetCurrentIP();
    void SetCurrentIP(std::string newIP);
private:
    int reputationRebel;
    int reputationCorpo;
    std::string CurrentIP;
    int CurrentDialogueID = -1;
    Person* CalledPerson;
};
