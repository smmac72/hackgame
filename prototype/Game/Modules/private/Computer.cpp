#include "../public/Computer.h"

Computer::Computer(std::string IP, int network, std::map<std::string, std::string> files, bool bIsHacked, bool bCanBeAccessed)
{
    this->IP = IP;
    this->network = network;
    this->files = files;
    this->bIsHacked = bIsHacked;
    this->bCanBeAccessed = bCanBeAccessed;
}

std::string Computer::GetIP()
{
    return IP;
}

void Computer::SetIP(const std::string& newIP)
{
    this->IP = newIP;
}

int Computer::GetNetwork() const
{
    return network;
}

void Computer::SetNetwork(int newNetwork)
{
    this->network = newNetwork;
}

std::map<std::string, std::string> Computer::GetFiles()
{
    return files;
}

void Computer::SetFiles(const std::map<std::string, std::string>& newFiles)
{
    this->files = newFiles;
}

bool Computer::GetIsHacked() const
{
    return bIsHacked;
}

void Computer::SetIsHacked(bool value)
{
    this->bIsHacked = value;
}

bool Computer::GetCanBeAccessed() const
{
    return bCanBeAccessed;
}

void Computer::SetCanBeAccessed(bool value)
{
    this->bCanBeAccessed = value;
}

void Computer::PrintComputer()
{
    std::cout << std::endl << "COMPUTER DATA" << std::endl;
    std::cout << "IP: " << IP << std::endl;
    std::cout << "Network ID: " << network << std::endl;
    std::cout << "Files: " << files.size() << std::endl;
    for (auto it : files)
    {
        std::cout << "\t" << it.first << " : " << it.second << std::endl;
    }
    std::cout << "Is hacked: " << bIsHacked << std::endl;
    std::cout << "Can be accessed (storywise): " << bCanBeAccessed << std::endl;
}

