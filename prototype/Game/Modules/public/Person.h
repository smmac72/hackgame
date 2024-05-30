#pragma once
#include <string>
#include <iostream>
#include "WIP - Phone.h"
#include "Computer.h"
#include "WIP - BankAccount.h"
#include "Factions.h"
#include "../../../Engine/Engine.h"

class Person
{
public:
    int GetID() const;
    void SetID(const int ID);
    std::string GetName() const;
    void SetName(const std::string& name);
    std::string GetRank() const;
    void SetRank(const std::string& name);
    int GetAge() const;
    void SetAge(const int age);
    Phone* GetPhone() const;
    void SetPhone(Phone* NewPhone);
    Computer* GetComputer() const;
    void SetComputer(Computer* NewComputer);
    BankAccount* GetBankAccount() const;
    void SetBankAccount(BankAccount* NewComputer);
    bool GetCanBeTargeted() const;
    void SetCanBeTargeted(bool value);
    EFactions GetFaction() const;
    void SetFaction(EFactions newFaction);

    std::string GetCurrentPlayerDialogue(int DialogueID);
    std::string GetCurrentPersonDialogue(int DialogueID);

    int LoadDialogue(int ID);
    bool bIsDialogueOver(int DialogueID);

    void PrintPerson() const;
    
    Person(int ID, std::string Name, std::string Rank, int Age, Phone* phone, Computer* computer, BankAccount* bank_account, bool bCanBeTargeted, EFactions faction);
    virtual ~Person();

protected:
    int ID;
    std::string Name;
    std::string Rank;
    int Age;

    Phone* PersonPhone;
    Computer* PersonComputer;
    BankAccount* PersonBankAccount;

    int CurrentDialogueID = 0;
    std::vector<std::string> PlayerDialogueStrings;
    std::vector<std::string> PersonDialogueStrings;

    bool bCanBeTargeted;
    EFactions faction;
};
