#ifndef PRINT_TABLE_
#define PRINT_TABLE_

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;

void printTable(const char * fileName);
void printHeader(const char * tableName, char * buffer,  size_t & lenBuffer);
void printBody(const char * tableName, char * buffer, size_t & lenBuffer);
void saveColumns(const char columnNames);
bool findColumns();

void printTable(const char * tableName) {

    size_t lenBuffer = 1024;
    char buffer[lenBuffer];

    printHeader(tableName, buffer, lenBuffer);
    printBody(tableName, buffer, lenBuffer);
}

void printHeader(const char * tableName, char * buffer, size_t & lenBuffer) {
    // print head of table (schema)
    ifstream schemasFile("./db/schema");

    if (schemasFile.is_open()) {
        int pos = 0;
        while (schemasFile.getline(buffer + pos, lenBuffer)) {
            char* token = strtok(buffer + pos, " # ");
            if(!strcmp(token,tableName)) {
                bool show = false;
                while(token != nullptr) {
                    if(show){
                        cout<<setw(20)<<left<<token<<setw(20)<<right;
                        show = false;
                    } else show = true;
                    token = strtok(nullptr, " # ");
                } 
                cout<<endl;
            }
        }
    } else {
        cout<<"Can't open file"<<"./db/schema"<<endl;
    }

    schemasFile.close();
}

void printBody(const char * tableName, char * buffer, size_t & lenBuffer) {
    // print row of the table
    char fileName[256];
    strcpy(fileName, "./db/");
    strcat(fileName, tableName);
    ifstream tableFile(fileName);

    if (tableFile.is_open()) {
        int pos = 0;
        while (tableFile.getline(buffer + pos, lenBuffer)) {

            char* token = strtok(buffer + pos, " # ");
            while(token != nullptr) {
                cout<<setw(20)<<left<<token;
                token = strtok(nullptr, " # ");
            }
            cout<<endl;

            pos += tableFile.gcount();

            if(pos >= sizeof(buffer)) {
                pos = 0;
            }
        }
    } else {
        cout<<"Can't open file "<<tableName<<endl;
    }

    tableFile.close();
}


void saveColumns(const char * columnNames, const char * tableName) {
    char * columns = strdup(columnNames);
    char * token = strtok(columns, ",");

    ofstream file("./db/columns");

    file<<tableName;
    while (token != nullptr)
    {
        file<<" # ";
        file<<string(token).substr(string(token).find_first_not_of(" "), string(token).find_last_not_of(" ") + 1);
        token = strtok(nullptr, ",");
    }           
    free(columns);
    file.close();
}


bool findColumns(const char * tableName) {
    int count = 0;
    ifstream schemaFile("./db/schema");
    ifstream columnsFile("./db/columns");

    if (schemasFile.is_open()) {
        int pos = 0;
        while (schemasFile.getline(buffer + pos, lenBuffer)) {
            char* token = strtok(buffer + pos, " # ");
            if(!strcmp(token,tableName)) {
                cout<<buffer + pos<<endl;
            }
        }
    } else {
        cout<<"Can't open file"<<"./db/schema"<<endl;
    }

    schemasFile.close();
}

#endif