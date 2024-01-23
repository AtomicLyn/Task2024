#pragma once
#include "Logger.hpp"

class LoggerLevelOne : public Logger
{
public:
	LoggerLevelOne(char* fileName);
	Logger* Write(Event event) override;
};