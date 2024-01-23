#pragma once
#include "Logger.hpp"

class LoggerLevelTwo : public Logger
{
public:
	LoggerLevelTwo(char* fileName);
	Logger* Write(Event event) override;
};