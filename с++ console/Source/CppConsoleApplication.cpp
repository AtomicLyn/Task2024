#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "Commands.hpp"
#include "LoggerLevelZero.hpp"
#include "LoggerLevelOne.hpp"
#include "LoggerLevelTwo.hpp"
#include "ParseInput.hpp"
#include "ThreadsLogic.hpp"
#include <thread>

using namespace std;

int main()
{
    std::string filename = "G:\\log.txt";
    char* cfilename = new char[filename.size() + 1];
    strcpy(cfilename, filename.c_str());

    Logger* logger = new LoggerLevelOne(cfilename);
    ThreadsLogic::SetLogger(logger);

    thread thirdThread(ThreadsLogic::ThirdThreadFunction);
    thread secondThread(ThreadsLogic::SecondThreadFunction);

    std::string input;
    bool exitStatus = false;
    while (!exitStatus)
    {
        cout << "--------------------------------------------" << endl;
        cout << "> date" << endl;
        cout << "> time" << endl;
        cout << "> exit" << endl;
        cout << "> faster <int>" << endl;
        cout << "> slower <int>" << endl;
        cout << "> pause" << endl;
        cout << "> resume" << endl;
        cout << "> level <int>" << endl;
        cout << "> stat" << endl;
        std::getline(std::cin, input);
        char* cinput = new char[input.size() + 1];
        strcpy(cinput, input.c_str());
        exitStatus = Commands::ExecuteCommand(cinput);
    } 

    ThreadsLogic::ExitProgram();
    secondThread.join();
    thirdThread.join();

    return 0;
}
