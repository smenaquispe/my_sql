#ifndef FIND_SCHEMA
#define FIND_SCHEMA

#include<vector>
#include<iostream>
#include<fstream>
#include"split.cpp"

using namespace std;

vector<string> findSchema(string nameSchema) {
    ifstream file("./db/schema");
    if(file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> schemaHead = splitString(line, '#');
            if(schemaHead.at(0) == nameSchema) {
                vector<string> nameColumns;
                for(int i = 1; i < schemaHead.size(); i += 2) 
                    nameColumns.push_back(schemaHead.at(i));
                return nameColumns;
            }
        }
    }

    vector<string> nullVect;
    return nullVect;
}

vector<string> findSchema(vector<string> columns, string nameSchema) {
    ifstream file("./db/schema");
    if(file.is_open()) {
        string line;
        while (getline(file, line)) {
            vector<string> schemaHead = splitString(line, '#');
            if(schemaHead.at(0) == nameSchema) {
                vector<string> nameColumns;
                for(int i = 1; i < schemaHead.size(); i += 2) {
                    for(const string c : columns) {
                        if(c == schemaHead.at(i)){
                            nameColumns.push_back(schemaHead.at(i));
                            nameColumns.push_back(schemaHead.at(i + 1));
                        }
                    }
                }
                return nameColumns;
            }
        }
    }

    vector<string> nullVect;
    return nullVect;
}

#endif