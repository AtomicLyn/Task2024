#include "Event.hpp"

using namespace std;

Event::Event(std::string date, std::string time, int eventId, int param1, int param2, int param3)
{
	this->date = date;
	this->time = time;
	this->eventId = eventId;
	this->param1 = param1;
	this->param2 = param2;
	this->param3 = param3;
}

string Event::GetDate() { return date; }
string Event::GetTime() { return time; }
int Event::GetEventId() { return eventId; }
int Event::GetParam1() { return param1; }
int Event::GetParam2() { return param2; }
int Event::GetParam3() { return param3; }