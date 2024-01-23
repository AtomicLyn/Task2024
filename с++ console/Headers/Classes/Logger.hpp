#pragma once
#include "Event.hpp"

class Logger
{
protected:
	static char* fileName;
	Logger(char* fileName);
	~Logger();
public:
	static Logger* GetLogger(int level);
	virtual Logger* Write(Event event) = 0;
};
