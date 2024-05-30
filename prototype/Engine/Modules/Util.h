#pragma once
#include <string>
#include <vector>
#include <sstream>

class Util
{
public:
    static std::vector<std::string> Split(const std::string &txt, char ch)
    {
        std::vector<std::string> strs;
        using namespace std;
        istringstream iss(txt);
        string s;
        while ( getline( iss, s, ch ) )
        {
            strs.push_back(s);
        }
        return strs;
    }
    static bool isNumber(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it))
            ++it;
        return !s.empty() && it == s.end();
    }
};
