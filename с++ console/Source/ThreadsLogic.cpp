#define _CRT_SECURE_NO_WARNINGS

#include"ThreadsLogic.hpp"
#include <ctime>
#include "LoggerLevelZero.hpp"

using namespace std;

vector<Event> ThreadsLogic::eventLog;
int ThreadsLogic::eventCount = 0;
Logger* ThreadsLogic::logger = new LoggerLevelZero(new char[0]);
int ThreadsLogic::interval = 1000;
bool ThreadsLogic::pause = false;
bool ThreadsLogic::exitProgram = false;
mutex ThreadsLogic::mutex;
condition_variable ThreadsLogic::cv;

void ThreadsLogic::SetLogger(Logger* lggr)
{
	logger = lggr;
}

void ThreadsLogic::SetLoggerLevel(int level)
{
	logger = logger->GetLogger(level);
}

void ThreadsLogic::SetIntervalFaster(int intv)
{
	if (interval - intv >= 100) interval -= intv;
}

void ThreadsLogic::SetIntervalSlower(int intv)
{
	interval += intv;
}

void ThreadsLogic::SetPause(bool ps)
{
	pause = ps;
}

void ThreadsLogic::ExitProgram()
{
	lock_guard<std::mutex> lock(mutex);
	exitProgram = true;
	cv.notify_all();
}

int ThreadsLogic::GetEventCount()
{
	return eventCount;
}

void ThreadsLogic::SecondThreadFunction()
{
	while (true)
	{
		if (exitProgram) break;

		if (!pause)
		{
			time_t t = time(nullptr);
			tm* now = localtime(&t);
			string date = to_string(now->tm_mday) + '.' + to_string(now->tm_mon + 1) + '.' + to_string(now->tm_year + 1900);
			string time = to_string(now->tm_hour) + ':' + to_string(now->tm_min) + ':' + to_string(now->tm_sec);

			Event event(date, time, 2, rand() % 10, rand() % 10, rand() % 10);

			{
				unique_lock<std::mutex> lock(mutex);
				eventLog.push_back(event);
			}

			++eventCount;
			cv.notify_one();		
		}

		this_thread::sleep_for(chrono::milliseconds(rand() % interval + 100));
	}
}

void ThreadsLogic::ThirdThreadFunction()
{
	while (true)
	{
		if (exitProgram) break;

		{
			unique_lock<std::mutex> lock(mutex);
			cv.wait(lock, [] { return !eventLog.empty() || exitProgram; });
		}


		while (!eventLog.empty())
		{
			Event event = eventLog.back();
			eventLog.pop_back();
			logger->Write(event);
		}
	}
}