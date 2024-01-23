#define _CRT_SECURE_NO_WARNINGS

#include "Commands.hpp"
#include <iostream>
#include <ctime>
#include "ParseInput.hpp"
#include "ThreadsLogic.hpp"

using namespace std;

map<string, func> Commands::funcMap = { 
    { "date", ShowDate },
    { "time", ShowTime },
    { "faster", SetFaster },
    { "slower", SetSlower },
    { "pause", Pause},
    { "resume", Resume },
    { "level", SetLoggerLevel },
    { "stat", ShowStat}
};

void Commands::ShowDate(vector<string> args)
{
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    string result = to_string(now->tm_mday) + '.' + to_string(now->tm_mon + 1) + '.' + to_string(now->tm_year + 1900);
    ShowText(result);
}

void Commands::ShowTime(vector<string> args)
{
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    string result = to_string(now->tm_hour) + ':' + to_string(now->tm_min) + ':' + to_string(now->tm_sec);
    ShowText(result);
}

void Commands::SetFaster(vector<string> args)
{
    try
    {
        int interval = atoi(args[0].c_str());
        ThreadsLogic::SetIntervalFaster(interval);
    }
    catch (exception e)
    {
        ShowError("Args parse error!");
    }
}

void Commands::SetSlower(vector<string> args)
{
    try
    {
        int interval = atoi(args[0].c_str());
        ThreadsLogic::SetIntervalSlower(interval);
    }
    catch (exception e)
    {
        ShowError("Args parse error!");
    }
}

void Commands::SetLoggerLevel(vector<string> args)
{
    try
    {
        int level = stoi(args[0]);
        if (level >= 0 && level <= 2) ThreadsLogic::SetLoggerLevel(level);
        else ShowError("level may be 0, 1 or 2");
    }
    catch (exception e)
    {
        ShowError("Args parse error!");
    }
}

void Commands::Pause(vector<string> args)
{
    ThreadsLogic::SetPause(true);
}

void Commands::Resume(vector<string> args)
{
    ThreadsLogic::SetPause(false);
}

void Commands::ShowStat(vector<string> args)
{
    int eventCount = ThreadsLogic::GetEventCount();
    string result = "Event count: " + to_string(eventCount);
    ShowText(result);
}

void Commands::ShowError(string err)
{
    cerr << err << endl;
}

void Commands::ShowText(string text)
{
    cout << text << endl;
}

bool Commands::ExecuteCommand(char* input)
{
    string str(input);

    string trimStr = ParseInput::Trim(str);

    if (trimStr.size() < 0)
    {
        ShowError("Null input!");
    }

    vector<string> args = ParseInput::ToArgs(trimStr);

    string command = args[0];

    vector<string> fArgs;
    copy(args.begin() + 1, args.end(), back_inserter(fArgs));

    if (command == "exit") return true;
    else if (funcMap.find(command) == funcMap.end()) ShowError("Undefined command!");
    else funcMap[command](fArgs);

    return false;
}