#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;
class Json
{
public:
    Json(const char* textJson);
    
    json GetJson();
    int GetObjectCount(const char* key);
    bool bDoesObjectExist(const char* key);
    void UpdateJson(json newJson);
    
private:
    json document_;
};