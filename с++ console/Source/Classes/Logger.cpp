#include "Logger.hpp"
#include "LoggerLevelZero.hpp"
#include "LoggerLevelOne.hpp"
#include "LoggerLevelTwo.hpp"

char* Logger::fileName = new char[0];

Logger::Logger(char* fileName)
{
	this->fileName = fileName;
}

Logger::~Logger() {}

Logger* Logger::GetLogger(int level)
{
	switch (level)
	{
	case 0: 
		return new LoggerLevelZero(fileName);
	case 1: 
		return new LoggerLevelOne(fileName);
	case 2: 
		return new LoggerLevelTwo(fileName);
	}
}