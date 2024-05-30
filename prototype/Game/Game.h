#pragma once
#include "../Engine/Engine.h"
#include "Modules/public/Player.h"
#include "Modules/public/SaveData.h"
#include "Modules/public/Window.h"

class Game
{
public:
    void Load();
    void Save();
    void Core();
    
    void ProcessMainMenu();
    void ProcessGame();
    void ProcessCall();
    bool ProcessCommand(const std::vector<std::string>& splitCommand);

    int GetVulnerabilityID();
    std::string GetVulnerabilityExploit(int vulnID);

    std::string GetQuestString(std::string filename);

    Person* FindPersonByID(int ID);
    Person* FindPersonByIP(std::string IP);
    Person* FindPersonByPhone(std::string Phone);

    Computer* FindComputerByPersonID(int ID);
    Computer* FindComputerByPerson(Person* person);
private:
    Player* player;
    std::vector<Person*> persons;
    SaveData* save_data;
    Window gameWindow;
};





