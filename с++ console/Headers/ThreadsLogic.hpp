#pragma once
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>
#include <string>
#include "Logger.hpp"
#include "Event.hpp"


class ThreadsLogic
{
private:
	static std::vector<Event> eventLog;
	static int eventCount;
	static Logger* logger;	
	static int interval;
	static bool pause;
	static bool exitProgram;
	static std::mutex mutex;
	static std::condition_variable cv;
public:
	static void SetLogger(Logger* logger);
	static void SetLoggerLevel(int level);
	static void SetIntervalFaster(int interval);
	static void SetIntervalSlower(int interval);
	static void SetPause(bool ps);
	static void ExitProgram();
	static int GetEventCount();
	static void SecondThreadFunction();	
	static void ThirdThreadFunction();
};