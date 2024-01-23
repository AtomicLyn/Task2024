#pragma once
#include <string>
#include <vector>
#include <map>

using func = void (*)(std::vector<std::string>);

class Commands
{
private:
	static std::map<std::string, func> funcMap;

	static void ShowDate(std::vector<std::string> args);
	static void ShowTime(std::vector<std::string> args);
	static void SetFaster(std::vector<std::string> args);
	static void SetSlower(std::vector<std::string> args);
	static void Pause(std::vector<std::string> args);
	static void Resume(std::vector<std::string> args);
	static void SetLoggerLevel(std::vector<std::string> args);
	static void ShowStat(std::vector<std::string> args);
	static void ShowError(std::string err);	
	static void ShowText(std::string text);
public:
	static bool ExecuteCommand(char* str);
};