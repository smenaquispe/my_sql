#ifndef SPLIT
#define SPLIT

#include<vector>
#include<iostream>
using namespace std;

/** make split of strings */
vector<string> splitString(const string& str, char delimiter) {
    vector<string> result;

    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        string substring = str.substr(start, end - start);
        substring.erase(remove_if(substring.begin(), substring.end(), ::isspace), substring.end());
        result.push_back(substring);
        start = end + 1;
        end = str.find(delimiter, start);
    }

    string substring = str.substr(start);
    substring.erase(remove_if(substring.begin(), substring.end(), ::isspace), substring.end());
    result.push_back(substring);

    return result;
}

/** recibe string*/
vector<string> splitString(const string& str, const string& delimiter) {
    vector<string> result;

    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != string::npos) {
        string substring = str.substr(start, end - start);
        substring.erase(remove_if(substring.begin(), substring.end(), ::isspace), substring.end());
        result.push_back(substring);
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    string substring = str.substr(start);
    substring.erase(remove_if(substring.begin(), substring.end(), ::isspace), substring.end());
    result.push_back(substring);

    return result;
}


#endif
