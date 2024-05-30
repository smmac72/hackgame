#pragma once
#include <iostream>
#include <string>
#include <map>

class Computer
{
public:
    Computer(std::string IP, int network, std::map<std::string, std::string> files, bool bIsHacked, bool bCanBeAccessed);

    std::string GetIP();
    void SetIP(const std::string& newIP);
    int GetNetwork() const;
    void SetNetwork(int newNetwork);
    std::map<std::string, std::string> GetFiles();
    void SetFiles(const std::map<std::string, std::string>& newFiles);
    bool GetIsHacked() const;
    void SetIsHacked(bool value);
    bool GetCanBeAccessed() const;
    void SetCanBeAccessed(bool value);

    void PrintComputer();
private:
    std::string IP;
    int network;
    std::map<std::string, std::string> files;
    bool bIsHacked;
    bool bCanBeAccessed;
};
