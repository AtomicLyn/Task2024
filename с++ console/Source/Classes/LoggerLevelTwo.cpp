#include "LoggerLevelTwo.hpp"
#include "Event.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

LoggerLevelTwo::LoggerLevelTwo(char* fileName) : Logger(fileName) {}

Logger* LoggerLevelTwo::Write(Event event)
{
	ofstream out(this->fileName, ios::app);
	string str = "Date: " + event.GetDate()
		+ " | " + "Time: " + event.GetTime()
		+ " | " + "EventId: " + to_string(event.GetEventId())
		+ " | " + "Param1: " + to_string(event.GetParam1())
		+ " | " + "Param2: " + to_string(event.GetParam2())
		+ " | " + "Param3: " + to_string(event.GetParam3());
	if (out.is_open())
	{
		out << str << endl;
	}
	out.close();
	return this;
}