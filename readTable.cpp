#ifndef READ_TABLE
#define READ_TABLE

#include<iostream>
#include<fstream>
#include<vector>
#include"split.cpp"

using namespace std;

vector< vector<string> > readTable(
    string nameTable, 
    vector<int> columns = {}
) {
    
    ifstream file("./db/" + nameTable);
    vector< vector<string> > content;

    if(file.is_open()) {
        string line;
        while (getline(file,line))
        {
            vector<string> row = splitString(line,'#');

            if(columns.size() > 0) {
                vector<string> customRow;
                for(const int c : columns) {
                    customRow.push_back(row.at(c));
                }
                content.push_back(customRow);

            } else {
                content.push_back(row);
            }
        }
        
    }

    return content;
}

vector< vector<string> > readTable(
    string nameTable, 
    int posCondition,
    bool (*condition)(string, string),
    string value,
    vector<int> positions = {}
) {
    
    ifstream file("./db/" + nameTable);
    vector< vector<string> > content;

    if(file.is_open()) {
        string line;
        while (getline(file,line))
        {
            vector<string> row = splitString(line,'#');

            if(!condition(row.at(posCondition), value)) {
                continue;
            }

            if(positions.size() > 0) {
                vector<string> customRow;
                for(const int p : positions) {
                    customRow.push_back(row.at(p));
                }
                content.push_back(customRow);

            } else {
                content.push_back(row);
            }
        }
        
    }

    return content;
}


#endif