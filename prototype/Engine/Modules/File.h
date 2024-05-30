// partly raii compliant file IO

#pragma once
#include <fstream>
#include <cassert>
#include <iomanip>
#include "Json.h"

class File
{
public:
    File(const char* name);
    ~File();
    std::string ReadFile();
    void WriteJson(const json newText);
private:
    std::fstream document;
    const char* name;
};