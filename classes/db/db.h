#ifndef DATA_BASE
#define DATA_BASE

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;

class DB
{
    private:
        char * tableName;
        char * columnsSelected;

        size_t lenBuffer;
        char * buffer;

        void printHeader();
        void printBody();
    public:
        DB();
        ~DB();

        // setters
        void setTable(char * tableName);
        void setColumns(char * columnNames);

        // other functions
        void printTable();
        void saveColumns();
};

DB::DB()
{
    lenBuffer = 1024;
    buffer = new char[lenBuffer];
}

DB::~DB()
{
    delete buffer;
}

#include"setters.h"
#include"printTable.h"
#include"saveColumns.h"

#endif