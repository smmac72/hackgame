#include "File.h"
File::File(const char* name)
{
    this->name = name;
    document.open(name);
    assert(document.is_open());
        
    /*
    todo: user can still mess with the data - throw exception in the future
    if (!document.is_open())s
        throw std::runtime_error("Failed to open file");
    */
}
File::~File()
{
    document.close();
}
std::string File::ReadFile()
{
    std::string out;
    std::string line;

    // byte order mark can mess this up
    // todo: check bom delete utf-8 bom if exists
    while (getline(document, line))
        out += line;
    return out;
}
void File::WriteJson(const json newText)
{
    document.close();
    document.open(name, std::ios::out | std::ios::trunc);
    document << std::setw(4) << newText << "\n";
}