#include "../public/SaveData.h"

Player* SaveData::InitPlayer()
{
    File file("ZaWarudo/Persons.json");
    Json json(file.ReadFile().c_str());
    Phone* newPlayerPhone = new Phone(json.GetJson()["player"]["Phone"]["Number"],
                                        json.GetJson()["player"]["Phone"]["bIsCallable"],
                                        json.GetJson()["player"]["Phone"]["bIsKnown"],
                                        json.GetJson()["player"]["Phone"]["bWasCalled"]
    );
    Computer* newPlayerComputer = new Computer(json.GetJson()["player"]["Computer"]["IP"],
                                                json.GetJson()["player"]["Computer"]["Network"],
                                                json.GetJson()["player"]["Computer"]["Files"],
                                                json.GetJson()["player"]["Computer"]["bIsHacked"],
                                                json.GetJson()["player"]["Computer"]["bCanBeAccessed"]
    );
    BankAccount* newPlayerBankAccount = new BankAccount(json.GetJson()["player"]["BankAccount"]["AccountID"],
                                                        json.GetJson()["player"]["BankAccount"]["Money"]
    );

    Player* returnPlayer = new Player(json.GetJson()["player"]["ID"],
                                    json.GetJson()["player"]["Name"],
                                    json.GetJson()["player"]["Rank"],
                                    json.GetJson()["player"]["Age"],
                                    newPlayerPhone,
                                    newPlayerComputer,
                                    newPlayerBankAccount,
                                    json.GetJson()["player"]["bCanBeTargeted"],
                                    EFactions::FACTION_CIVIL,
                                    json.GetJson()["player"]["ReputationRebel"],
                                    json.GetJson()["player"]["ReputationCorpo"]
    );
    return returnPlayer;
}
std::vector<Person*> SaveData::InitPersons()
{
    File file("ZaWarudo/Persons.json");
    Json json(file.ReadFile().c_str());
    
    std::vector<Person*> returnPersons;
    int persons = json.GetObjectCount("persons");
    for (int i = 0; i < persons; i++)
    {
        Phone* newPlayerPhone = new Phone(json.GetJson()["persons"][i]["Phone"]["Number"],
                                        json.GetJson()["persons"][i]["Phone"]["bIsCallable"],
                                        json.GetJson()["persons"][i]["Phone"]["bIsKnown"],
                                        json.GetJson()["persons"][i]["Phone"]["bWasCalled"]
        );
        Computer* newPlayerComputer = new Computer(json.GetJson()["persons"][i]["Computer"]["IP"],
                                                    json.GetJson()["persons"][i]["Computer"]["Network"],
                                                    json.GetJson()["persons"][i]["Computer"]["Files"],
                                                    json.GetJson()["persons"][i]["Computer"]["bIsHacked"],
                                                    json.GetJson()["persons"][i]["Computer"]["bCanBeAccessed"]
        );
        BankAccount* newPlayerBankAccount = new BankAccount(json.GetJson()["persons"][i]["BankAccount"]["AccountID"],
                                                            json.GetJson()["persons"][i]["BankAccount"]["Money"]
        );

        Person* appendPerson = new Person(json.GetJson()["persons"][i]["ID"],
                                        json.GetJson()["persons"][i]["Name"],
                                        json.GetJson()["persons"][i]["Rank"],
                                        json.GetJson()["persons"][i]["Age"],
                                        newPlayerPhone,
                                        newPlayerComputer,
                                        newPlayerBankAccount,
                                        json.GetJson()["persons"][i]["bCanBeTargeted"],
                                        EFactions::FACTION_CIVIL
        );

        returnPersons.push_back(appendPerson);
    }
    return returnPersons;
}

bool SaveData::Save(Player* player, std::vector<Person*> persons)
{
    json newSaveFile;

    // player
    json playerID = {"ID", player->GetID() };
    json playerName = {"Name", player->GetName() };
    json playerRank = {"Rank", player->GetRank() };
    json playerAge = {"Age", player->GetAge() };
    json playerPhone = {"Phone", { {"Number", player->GetPhone()->GetNumber() }, {"bIsCallable", player->GetPhone()->GetIsCallable() }, {"bIsKnown", player->GetPhone()->GetIsKnown()}, {"bWasCalled", player->GetPhone()->GetWasCalled()} } };
    json playerBankAccount { "BankAccount", { { "AccountID", player->GetBankAccount()->GetAccountID() },  { "Money", player->GetBankAccount()->GetMoney() } } };
    json playerCanBeTargeted = {"bCanBeTargeted", player->GetCanBeTargeted() };
    json faction = {"Faction", 0 }; // todo: fix
    json reputationRebel = {"ReputationRebel", player->GetReputationRebel() };
    json reputationCorpo = {"ReputationCorpo", player->GetReputationCorpo() };
    
    // for computer
    std::map<std::string, std::string> computerFiles = {};
    for (auto it : player->GetComputer()->GetFiles())
    {
        json currentFile = { it.first, it.second };
        computerFiles.insert(currentFile);
    }
    json playerComputer = {"Computer", { {"IP", player->GetComputer()->GetIP() }, {"Network", player->GetComputer()->GetNetwork() }, {"Files", computerFiles}, {"bIsHacked", player->GetComputer()->GetIsHacked()}, {"bCanBeAccessed", player->GetComputer()->GetCanBeAccessed() } } };
    
    json jsonPlayerData ={ playerID, playerName, playerRank, playerAge, playerPhone, playerComputer, playerBankAccount, playerCanBeTargeted, faction, reputationRebel, reputationCorpo };

    // other persons
    std::vector<json> jsonPersonData;
    for (auto it = persons.begin(); it < persons.end(); ++it)
    {
        // main person data
        json personID = {"ID", (*it)->GetID() };
        json personName = {"Name", (*it)->GetName() };
        json personRank = {"Rank", (*it)->GetRank() };
        json personAge = {"Age", (*it)->GetAge() };
        json personPhone = {"Phone", { {"Number", (*it)->GetPhone()->GetNumber() }, {"bIsCallable", (*it)->GetPhone()->GetIsCallable() }, {"bIsKnown", (*it)->GetPhone()->GetIsKnown()}, {"bWasCalled", (*it)->GetPhone()->GetWasCalled()} } };
        json personBankAccount { "BankAccount", { { "AccountID", (*it)->GetBankAccount()->GetAccountID() },  { "Money", (*it)->GetBankAccount()->GetMoney() } } };
        json personCanBeTargeted = {"bCanBeTargeted", (*it)->GetCanBeTargeted() };
        json personFaction = {"Faction", 0 }; // todo: fix
    
        // for computer
        computerFiles = {};
        for (auto computerIt : (*it)->GetComputer()->GetFiles())
        {
            json currentFile = { computerIt.first, computerIt.second };
            computerFiles.insert(currentFile);
        }
        json personComputer = {"Computer", { {"IP", (*it)->GetComputer()->GetIP() }, {"Network", (*it)->GetComputer()->GetNetwork() }, {"Files", computerFiles}, {"bIsHacked", (*it)->GetComputer()->GetIsHacked()}, {"bCanBeAccessed", (*it)->GetComputer()->GetCanBeAccessed() } } };
    
        json rawPersonData = { personID, personName, personRank, personAge, personPhone, personComputer, personBankAccount, personCanBeTargeted, personFaction };
        jsonPersonData.emplace_back(rawPersonData);
    }

    newSaveFile.emplace("player", jsonPlayerData);
    newSaveFile.emplace("persons",  jsonPersonData);
    
    File file("ZaWarudo/Persons.json");
    file.WriteJson(newSaveFile);
    return true;
}