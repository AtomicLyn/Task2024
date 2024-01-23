#define _CRT_SECURE_NO_WARNINGS

#include "ParseInput.hpp"
#include <sstream>
#include <vector>

using namespace std;

string ParseInput::Trim(string str)
{
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');

    if (first == std::string::npos || last == std::string::npos) {
        return "";
    }

    string trimStr = str.substr(first, last - first + 1);

    return trimStr;
}

vector<string> ParseInput::ToArgs(string str)
{
    istringstream iss(str);
    vector<string> words;

    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}