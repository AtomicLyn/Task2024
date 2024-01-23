#pragma once
#include <string>

class Event
{
private:
	std::string date, time;
	int eventId, param1, param2, param3;
public:
	Event(std::string date, std::string time, int eventId, int param1, int param2, int param3);

	std::string GetDate();
	std::string GetTime();
	int GetEventId();
	int GetParam1();
	int GetParam2();
	int GetParam3();
};
