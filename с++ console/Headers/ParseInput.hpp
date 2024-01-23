#pragma once
#include <string>
#include <vector>

class ParseInput
{
public:	
	static std::string Trim(std::string str);
	static std::vector<std::string> ToArgs(std::string str);
};