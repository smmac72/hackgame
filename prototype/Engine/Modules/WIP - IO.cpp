// todo: windowsevents.cpp - get events, double buffer screen update - no flickering when cleaned
// no need now
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>

class IO
{
public:
	void UpdateHeader()
	{

	}
	void Clear()
	{
		buffer.clear();
		system("CLS");
	}
	void PrintHeader()
	{

	}
	void PrintBuffer()
	{
		for (std::string str : buffer)
			std::cout << str << std::endl; // todo replace with printf when time comes
	}
	void AddMessage(std::string newOutput)
	{
		std::cout << newOutput << std::endl;
		buffer.push_back(newOutput);
	}
	void NewMessage(std::string newOutput)
	{
		Clear();
		AddMessage(newOutput);
	}
private:
	std::vector<std::string> header;
	std::vector<std::string> buffer;
};
