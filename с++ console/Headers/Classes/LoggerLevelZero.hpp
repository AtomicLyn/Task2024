#pragma once
#include "Logger.hpp"

class LoggerLevelZero : public Logger
{
public:
	LoggerLevelZero(char* fileName);
	Logger* Write(Event event) override;
};