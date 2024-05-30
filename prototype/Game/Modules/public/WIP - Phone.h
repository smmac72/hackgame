#pragma once
#include "../../../Engine/Engine.h"
#include <string>
#include <windows.h>

class Phone
{
public:
    Phone(std::string number, bool bIsCallable, bool bIsKnown, bool bWasCalled);
    std::string GetNumber() const;
    void SetNumber(std::string number);
    bool GetIsCallable() const;
    void SetIsCallable(bool value);
    bool GetIsKnown() const;
    void SetIsKnown(bool value);
    bool GetWasCalled() const;
    void SetWasCalled(bool value);
    void Call(const int dialogueID);
private:
    std::string number;
    bool bIsCallable;
    bool bIsKnown;
    bool bWasCalled;
};
