#include "Json.h"
Json::Json(const char* textJson)
{
    document_ = json::parse(textJson);
    assert(document_.is_object());
}
json Json::GetJson()
{
    assert(!document_.is_null());
    return document_;
}
int Json::GetObjectCount(const char* key)
{
    assert(!document_[key].is_null());
    return static_cast<int>(document_[key].size());
}

bool Json::bDoesObjectExist(const char* key)
{
    return !document_[key].is_null();
}

void Json::UpdateJson(json newJson)
{
    document_ = newJson;
}