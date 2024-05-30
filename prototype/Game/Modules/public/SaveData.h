#pragma once
#include "../../../Engine/Engine.h"
#include "Player.h"

class SaveData
{
public:
    Player* InitPlayer();
    static std::vector<Person*> InitPersons();
    
    bool Save(Player* player, std::vector<Person*> persons);
};
