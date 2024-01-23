#include "LoggerLevelOne.hpp"
#include "Event.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

LoggerLevelOne::LoggerLevelOne(char* fileName) : Logger(fileName) {}

Logger* LoggerLevelOne::Write(Event event)
{
	ofstream out(this->fileName, ios::app);
	string str = "Date: " + event.GetDate()
		+ " | " + "Time: " + event.GetTime()
		+ " | " + "EventId: " + to_string(event.GetEventId())
		+ " | " + "Param1: " + to_string(event.GetParam1());
	if (out.is_open())
	{
		out << str << endl;
	}
	out.close();
	return this;
}