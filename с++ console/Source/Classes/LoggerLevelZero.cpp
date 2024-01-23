#include "LoggerLevelZero.hpp"
#include "Event.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

LoggerLevelZero::LoggerLevelZero(char* fileName) : Logger(fileName) {}

Logger* LoggerLevelZero::Write(Event event)
{
	ofstream out(fileName, ios::app);
	string str = "Time: " + event.GetTime() + " | " + "EventId: " + to_string(event.GetEventId());
	if (out.is_open())
	{
		out << str << endl;
	}
	out.close();	
	return this;
}

