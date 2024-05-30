#include "../public/WIP - Phone.h"
Phone::Phone(std::string number, bool bIsCallable, bool bIsKnown, bool bWasCalled)
{
    this->number = number;
    this->bIsCallable = bIsCallable;
    this->bIsKnown = bIsKnown;
    this->bWasCalled = bWasCalled;
}

std::string Phone::GetNumber() const
{
    return number;
}

void Phone::SetNumber(std::string number)
{
    this->number = number;
}

bool Phone::GetIsCallable() const
{
    return bIsCallable;
}

void Phone::SetIsCallable(bool value)
{
    this->bIsCallable = value;
}

bool Phone::GetIsKnown() const
{
    return bIsKnown;
}

void Phone::SetIsKnown(bool value)
{
    this->bIsKnown = value;
}

bool Phone::GetWasCalled() const
{
    return bWasCalled;
}

void Phone::SetWasCalled(bool value)
{
    this->bWasCalled = value;
}

void Phone::Call(const int dialogueID)
{

}
