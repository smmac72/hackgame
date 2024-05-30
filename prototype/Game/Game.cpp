#include "Game.h"

void Game::Load()
{
    player = save_data->InitPlayer();
    persons = save_data->InitPersons();

    player->SetCurrentIP(player->GetComputer()->GetIP());
}

void Game::Save()
{
    save_data->Save(player, persons);
}

bool Game::ProcessCommand(const std::vector<std::string>& splitCommand)
{
    if (splitCommand.empty())
        return false;

    if (splitCommand[0] == "debug_stats") // todo remove, show player stats (no args) or any person stats (arg - id)
    {
        if (splitCommand.size() == 1)
        {
            player->PrintPlayer();
            return true;
        }
        if (Util::isNumber(splitCommand[1]))
        {
            Person* foundPerson = FindPersonByID(std::stoi(splitCommand[1]));
            if (!foundPerson)
            {
                std::cout << "No such person found" << std::endl;
                return false;
            }
            foundPerson->PrintPerson();
            return true;
        }
        return false;
    }
    if (splitCommand[0] == "debug_pc")
    {
        if (splitCommand.size() == 1)
        {
            Computer* foundComputer = FindComputerByPersonID(1);
            foundComputer->PrintComputer();
            return true;
        }
        if (Util::isNumber(splitCommand[1]))
        {
            Computer* foundComputer = FindComputerByPersonID(std::stoi(splitCommand[1]));
            if (!foundComputer)
            {
                std::cout << "No such person found" << std::endl;
                return false;
            }
            foundComputer->PrintComputer();
            return true;
        }
        return false;
    }
    if (splitCommand[0] == "ls")
    {
        Computer* viewable = FindComputerByPerson(FindPersonByIP(player->GetCurrentIP()));
        if (!viewable->GetIsHacked())
        {
            std::cout << "No access" << std::endl;
            return false;
        }
        std::cout << "Files: " << viewable->GetFiles().size() << std::endl;
        for (auto it : viewable->GetFiles())
        {
            std::cout << "\t" << it.first << std::endl;
        }
    }
    if (splitCommand[0] == "cat") // only output todo: do something snake
    {
        if (splitCommand.size() < 2)
        {
            std::cout << "use: cat [filename]" << std::endl;
            return false;
        }
        
        Computer* viewable = FindComputerByPerson(FindPersonByIP(player->GetCurrentIP()));
        if (!viewable->GetIsHacked())
        {
            std::cout << "No access" << std::endl;
            return false;
        }
        for (auto it : viewable->GetFiles())
        {
            if (splitCommand[1] == "*" || it.first == splitCommand[1])
            {
                std::cout << "\t" << it.first << " : " << it.second << std::endl;

                if (splitCommand[1] != "*")
                    return true;
            }
        }
        if (splitCommand[1] == "*")
            return true;
        std::cout << "No such file found" << std::endl;
        return false;
    }
    if (splitCommand[0] == "scan")
    {
        std::cout << "\t Your machine: " << player->GetComputer()->GetIP() << std::endl;
        for (auto it = persons.begin(); it < persons.end(); ++it)
        {
            if (player->GetComputer()->GetNetwork() == (*it)->GetComputer()->GetNetwork())
                std::cout << "\t " << (*it)->GetComputer()->GetIP() << " | " << ((*it)->GetComputer()->GetIsHacked() ? "Hacked" : "Not hacked") << std::endl;
        }
        return true;
    }
    if (splitCommand[0] == "connect")
    {
        if (splitCommand.size() < 2)
        {
            std::cout << "use: connect [ip]" << std::endl;
            return false;
        }
        Person* connectedPerson = FindPersonByIP(splitCommand[1]);
        if (!connectedPerson)
        {
            std::cout << "Cannot reach host" << std::endl;
            return false;
        }
        /* no networks implemented - todo maybe
        if (connectedPerson->GetComputer()->GetNetwork() != player->GetComputer()->GetNetwork())
        {
            std::cout << "Cannot reach host" << std::endl;
            return false;
        }*/
        player->SetCurrentIP(splitCommand[1]);
        return true;
    }
    if (splitCommand[0] == "disconnect")
    {
        player->SetCurrentIP(player->GetComputer()->GetIP());
        return true;
    }
    if (splitCommand[0] == "hack")
    {
        Computer* viewable = FindComputerByPerson(FindPersonByIP(player->GetCurrentIP()));
        if (viewable->GetIsHacked())
        {
            std::cout << "Already root" << std::endl;
            return false;
        }
        int VulnPort = GetVulnerabilityID();
        std::cout << "Vulnerability found - port " << VulnPort << " | " << GetVulnerabilityExploit(VulnPort) << " exploit worked successfully." << std::endl;
        if (FindPersonByIP(player->GetCurrentIP())->GetFaction() == EFactions::FACTION_CORPO)
        {
            std::cout << "You left your trace on a corpo machine. [-5 corpo credit]" << std::endl;
            player->SetReputationCorpo(player->GetReputationCorpo() - 5);
        }
        if (FindPersonByIP(player->GetCurrentIP())->GetFaction() == EFactions::FACTION_REBEL)
        {
            std::cout << "You've successfully infiltrated a rebel machine. [+5 corpo credit]" << std::endl;
            player->SetReputationCorpo(player->GetReputationCorpo() + 5);
        }
        viewable->SetIsHacked(true);
        return true;
    }
    if (splitCommand[0] == "scp")
    {
        if (splitCommand.size() < 2)
        {
            std::cout << "use: scp [filename]" << std::endl;
            return false;
        }
        
        Computer* viewable = FindComputerByPerson(FindPersonByIP(player->GetCurrentIP()));
        if (!viewable->GetIsHacked())
        {
            std::cout << "No access" << std::endl;
            return false;
        }
        for (auto it : viewable->GetFiles())
        {
            if (splitCommand[1] == "*" || it.first == splitCommand[1])
            {
                std::map<std::string, std::string> newTempFile = player->GetComputer()->GetFiles();
                newTempFile[it.first] = it.second;
                player->GetComputer()->SetFiles(newTempFile);
                std::cout << "Copied " << it.first << " to local" << std::endl;

                if (splitCommand[1] != "*")
                    return true;
            }
        }
        if (splitCommand[1] == "*")
            return true;
        std::cout << "No such file found" << std::endl;
        return false;
    }
    // todo: merge logic - equal filenames in source/destination
    if (splitCommand[0] == "mv")
    {
        if (splitCommand.size() < 2)
        {
            std::cout << "use: mv [filename]" << std::endl;
            return false;
        }
        
        Computer* viewable = FindComputerByPerson(FindPersonByIP(player->GetCurrentIP()));
        if (!viewable->GetIsHacked())
        {
            std::cout << "No access" << std::endl;
            return false;
        }
        for (auto it : viewable->GetFiles())
        {
            if (splitCommand[1] == "*" || it.first == splitCommand[1])
            {
                std::map<std::string, std::string> newTempFile = player->GetComputer()->GetFiles();
                std::map<std::string, std::string> newStolenFile = viewable->GetFiles();
                newStolenFile.erase(it.first);
                newTempFile[it.first] = it.second;
                player->GetComputer()->SetFiles(newTempFile);
                viewable->SetFiles(newStolenFile);
                std::cout << "Moved " << it.first << " to local" << std::endl;

                std::string NewQuest = GetQuestString(it.first);
                if (NewQuest.size())
                {
                    std::cout << NewQuest << std::endl;
                }
                if (splitCommand[1] != "*")
                    return true;
            }
        }
        if (splitCommand[1] == "*")
            return true;
        std::cout << "No such file found" << std::endl;
        return false;
    }
    if (splitCommand[0] == "call")
    {
        if (splitCommand.size() < 2)
        {
            std::cout << "use: call [phone number]" << std::endl;
            return false;
        }
        Person* viewable = FindPersonByPhone(splitCommand[1]);
        if (!viewable)
        {
            std::cout << "[Call] No response" << std::endl;
            return false;
        }
        if (!viewable->GetPhone()->GetIsCallable())
        {
            std::cout << "[Call] No response" << std::endl;
            return false;
        }
        if (!viewable->GetPhone()->GetIsKnown())
        {
            std::cout << "[Call] No response" << std::endl;
            return false;
        }
        if (viewable->GetPhone()->GetWasCalled())
        {
            std::cout << "[Call] No response" << std::endl;
            return false;
        }
        player->MoveDialogueID();
        if (viewable->LoadDialogue(player->GetDialogueID()) == -1)
            return false;
        FindPersonByID(2)->LoadDialogue(player->GetDialogueID());
        player->SetCalledPerson(viewable);
        gameWindow.SetWindowState(EWindowStates::WINDOW_CALL);
        return true;
    }
    if (splitCommand[0] == "rm")
    {
        if (splitCommand.size() < 2)
        {
            std::cout << "use: rm [filename]" << std::endl;
            return false;
        }
        
        Computer* viewable = FindComputerByPerson(FindPersonByIP(player->GetCurrentIP()));
        if (!viewable->GetIsHacked())
        {
            std::cout << "No access" << std::endl;
            return false;
        }
        for (auto it : viewable->GetFiles())
        {
            if (splitCommand[1] == "*" || it.first == splitCommand[1])
            {
                std::map<std::string, std::string> newStolenFile = viewable->GetFiles();
                newStolenFile.erase(it.first);
                viewable->SetFiles(newStolenFile);
                std::cout << "Erased " << it.first << std::endl;
                
                if (splitCommand[1] != "*")
                    return true;
            }
        }
        if (splitCommand[1] == "*")
            return true;
        std::cout << "No such file found" << std::endl;
        return false;
    }
    if (splitCommand[0] == "transfer")
    {
        std::cout << "[Bank] Sberbank is not operational. Their servers are down" << std::endl;
        return false;
        // transfer todo - no bank ideas rn
    }
    if (splitCommand[0] == "save")
    {
        save_data->Save(player, persons);
        if (player->GetCurrentIP() != player->GetComputer()->GetIP())
        {
            std::cout << "You left your save trace on somebody's machine. [-5 corpo credit]" << std::endl;
            player->SetReputationCorpo(player->GetReputationCorpo() - 5);
        }
            
        std::cout << "Saved successfully" << std::endl;
        return true;
    }
    if (splitCommand[0] == "man")
    {
        std::cout << "scan - get devices on your network" << std::endl;
        std::cout << "ls - get all files on the current machine" << std::endl;
        std::cout << "cat [filename] - get file contents (no I in IO)" << std::endl;
        std::cout << "connect [ip] - connect to a remote machine" << std::endl;
        std::cout << "disconnect - return to your local machine" << std::endl;
        std::cout << "hack - standard issue port vulnerability scanner" << std::endl;
        std::cout << "scp [filename] - copy file to your local machine" << std::endl;
        std::cout << "mv [filename] - move file to your local machine" << std::endl;
        std::cout << "call [number] - give somebody a call" << std::endl;
        std::cout << "rm [filename] - remove file from the current machine" << std::endl;
        std::cout << "save - save za warudo" << std::endl;
        std::cout << "shutdown" << std::endl;
        std::cout << "man - this page" << std::endl;
    }
    if (splitCommand[0] == "shutdown")
    {
        gameWindow.SetWindowState(EWindowStates::WINDOW_EXIT);
        return true;
    }
    return false;
}

int Game::GetVulnerabilityID()
{
    return 3389; // todo - add new, store in json in player as arr. all demo computers have 3389 remote access vuln
}

std::string Game::GetVulnerabilityExploit(int vulnID)
{
    switch (vulnID)
    {
    case 3389:
        return "Remote desktop";
    }
    return std::string();
}

std::string Game::GetQuestString(std::string filename) // todo json maybe, prioritize other stuff
{
    if (filename == "control")
    {
        return "[Quest] New quest: Find a way to get out. You won't. The tutorial is over";
    }
    return std::string();
}

void Game::ProcessCall()
{
    int CurrentDialogueID = player->GetDialogueID();
    if (player->GetCalledPerson()->bIsDialogueOver(CurrentDialogueID))
    {
        player->ResetDialogueID();
        player->NullCalledPerson();
        std::cout << "[Call] Call ended" << std::endl;
        gameWindow.SetWindowState(EWindowStates::WINDOW_GAME);
        return;
    }
    std::cout << player->GetCalledPerson()->GetCurrentPersonDialogue(player->GetDialogueID()) << std::endl;
    player->MoveDialogueID();
    getchar();
    std::cout << player->GetCalledPerson()->GetCurrentPlayerDialogue(player->GetDialogueID()) << std::endl << std::endl;
}

// todo remove std io, use winmessages for seamless input + window update
// for demo purposes only
void Game::ProcessGame()
{
    std::string command;
    std::vector<std::string> splitCommand;
    while (gameWindow.GetWindowState() != EWindowStates::WINDOW_EXIT)
    {
        if (gameWindow.GetWindowState() == EWindowStates::WINDOW_CALL)
            ProcessCall();
        else
        {
            std::getline(std::cin, command);
            splitCommand = Util::Split(command, ' ');
            ProcessCommand(splitCommand);
        }
        
    }
}

void Game::Core()
{
    Load();
    while (gameWindow.GetWindowState() != EWindowStates::WINDOW_EXIT)
    {
        switch(gameWindow.GetWindowState())
        {
        case EWindowStates::WINDOW_MAINMENU:
            ProcessMainMenu();
            break;
        case EWindowStates::WINDOW_GAME:
            ProcessGame();
            break;
        case EWindowStates::WINDOW_CALL:
            ProcessCall();
            break;
        case EWindowStates::WINDOW_EXIT:
            break;
        }
    }
}

Person* Game::FindPersonByID(int ID)
{
    if (player->GetID() == ID) // not sure perhaps bad, do not use
        return player;
    for (auto it = persons.begin(); it < persons.end(); ++it)
    {
        if ((*it)->GetID() == ID)
            return *it;
    }
    return nullptr;
}

Person* Game::FindPersonByIP(std::string IP)
{
    if (player->GetComputer()->GetIP() == IP) 
        return player;
    for (auto it = persons.begin(); it < persons.end(); ++it)
    {
        if ((*it)->GetComputer()->GetIP() == IP)
            return *it;
    }
    return nullptr;
}

Person* Game::FindPersonByPhone(std::string Phone)
{
    if (player->GetPhone()->GetNumber() == Phone)
        return player;
    for (auto it = persons.begin(); it < persons.end(); ++it)
    {
        if ((*it)->GetPhone()->GetNumber() == Phone)
            return *it;
    }
    return nullptr;
}

Computer* Game::FindComputerByPerson(Person* person)
{
    if (player == person)
        return player->GetComputer();
    for (auto it = persons.begin(); it < persons.end(); ++it)
    {
        if ((*it) == person)
            return (*it)->GetComputer();
    }
    return nullptr;
}
Computer* Game::FindComputerByPersonID(int ID)
{
    if (player->GetID() == ID)
        return player->GetComputer();
    for (auto it = persons.begin(); it < persons.end(); ++it)
    {
        if ((*it)->GetID() == ID)
            return (*it)->GetComputer();
    }
    return nullptr;
}

void Game::ProcessMainMenu()
{
    std::cout << "login: " << player->GetName() << std::endl;
    std::cout << "password: ";

    std::string password;
    std::cin >> password;

    std::cout << "login successful" << std::endl;
    std::cout << "[Quest] Current quest: Find out anything about your new workplace. Use 'man' for help" << std::endl;
    gameWindow.SetWindowState(EWindowStates::WINDOW_GAME);
}

