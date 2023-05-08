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
        char * newSchemaName;

        char *defaultName;

        // where clause 
        char * columnCompare;
        char * valueCompare;
        bool (*condition)(char *, char *);

        size_t lenBuffer;
        char * buffer;

        void printHeader(bool);
        void printBody(bool);

    public:
        DB();
        ~DB();

        // setters
        void setTable(char * tableName);
        void setColumns(char * columnNames);
        void setNewSchemaName(char * schemaName);

        void setColumnCompare(char * columnCompare);
        void setValueCompare(char * valueCompare);
        void setCondition(bool (*condition)(char * , char *));

        // other functions
        void printTable();
        void printNewTable();
        void saveColumns();
        void createSchema();
        void createTable();
};

DB::DB()
{
    lenBuffer = 1024;
    buffer = new char[lenBuffer];
    newSchemaName = NULL;

    defaultName = new char[12];
    strcpy(defaultName,"default_name");
}

DB::~DB()
{
    delete buffer;
    delete [] defaultName;
}

#include"setters.h"
#include"printTable.h"
#include"saveColumns.h"
#include"createSchema.h"
#include"createTable.h"

#endif