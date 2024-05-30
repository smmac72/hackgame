#include "../public/Person.h"
int Person::GetID() const
{
    return ID;
}
void Person::SetID(const int ID)
{
    this->ID = ID;
}
std::string Person::GetName() const
{
    return Name;
}
void Person::SetName(const std::string& name)
{
    this->Name = name;
}

std::string Person::GetRank() const
{
    return Rank;
}

void Person::SetRank(const std::string& newRank)
{
    this->Rank = newRank;
}

int Person::GetAge() const
{
    return Age;
}
void Person::SetAge(const int age)
{
    this->Age = age;
}
Phone* Person::GetPhone() const
{
    return PersonPhone;
}
void Person::SetPhone(Phone* NewPhone)
{
    this->PersonPhone = NewPhone;
}
Computer* Person::GetComputer() const
{
    return PersonComputer;
}
void Person::SetComputer(Computer* NewComputer)
{
    this->PersonComputer = NewComputer;
}

BankAccount* Person::GetBankAccount() const
{
    return PersonBankAccount;
}

void Person::SetBankAccount(BankAccount* bankAccount)
{
    this->PersonBankAccount = bankAccount;
}

bool Person::GetCanBeTargeted() const
{
    return bCanBeTargeted;
}

void Person::SetCanBeTargeted(bool value)
{
    this->bCanBeTargeted = value;
}

EFactions Person::GetFaction() const
{
    return faction;
}

void Person::SetFaction(EFactions newFaction)
{
    this->faction = newFaction;
}

bool Person::bIsDialogueOver(int DialogueID)
{
    return DialogueID >= PlayerDialogueStrings.size() && DialogueID >= PersonDialogueStrings.size();
}
std::string Person::GetCurrentPlayerDialogue(int DialogueID)
{
    if (DialogueID >= PlayerDialogueStrings.size())
        return "[You] ...";
    return "[You] " + PlayerDialogueStrings[DialogueID];
}
std::string Person::GetCurrentPersonDialogue(int DialogueID)
{
    if (DialogueID >= PersonDialogueStrings.size())
        return "[" + Name + "] ...";
    return "[" + Name + "] " + PersonDialogueStrings[DialogueID];
}

int Person::LoadDialogue(int dialogueID)
{
    PlayerDialogueStrings.clear();
    PersonDialogueStrings.clear();
    File file("ZaWarudo/Dialogues.json");
    Json json(file.ReadFile().c_str());
    int dialogues = json.GetObjectCount("dialogues");
    for (int i = 0; i < dialogues; i++)
    {
        int tmpPersonID, tmpDialogueID;
        tmpPersonID = json.GetJson()["dialogues"][i]["PersonID"];
        tmpDialogueID = json.GetJson()["dialogues"][i]["DialogueID"];
        if (ID == tmpPersonID && dialogueID == tmpDialogueID)
        {
            int PlayerLines = json.GetJson()["dialogues"][i]["PlayerLines"].size();
            for (int j = 0; j < PlayerLines; j++)
            {
                PlayerDialogueStrings.push_back(json.GetJson()["dialogues"][i]["PlayerLines"][j]);
            }
            int PersonLines = json.GetJson()["dialogues"][i]["PersonLines"].size();
            for (int j = 0; j < PersonLines; j++)
                PersonDialogueStrings.push_back(json.GetJson()["dialogues"][i]["PersonLines"][j]);
            return dialogueID;
        }
    }
    return -1;
}

Person::Person(int ID, std::string Name, std::string Rank, int Age, Phone* phone, Computer* computer, BankAccount* bank_account, bool bCanBeTargeted, EFactions faction)
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
}
Person::~Person() { }
// debug
// todo: remove
void Person::PrintPerson() const
{
    std::cout << std::endl << "PERSON DATA" << std::endl;
    std::cout << "ID " << ID << std::endl;
    std::cout << "Name " << Name << std::endl;
    std::cout << "Rank " << Rank << std::endl;
    std::cout << "Age " << Age << std::endl;
    std::cout << "Phone number " << PersonPhone->GetNumber() << std::endl;
    std::cout << "IP address " << PersonComputer->GetIP() << std::endl;
    std::cout << "Money on account " << PersonBankAccount->GetMoney() << std::endl;
    std::cout << "Can be contract target " << bCanBeTargeted << std::endl;
}