#ifndef SETTERS
#define SETTERS

#include"db.h"

void DB::setTable(char * tableName) {
    this->tableName = tableName;
}

void DB::setColumns(char * columnNames) {
    this->columnsSelected = columnNames;
}

void DB::setNewSchemaName(char * schemaName) {
    this->newSchemaName = schemaName;
}

#endif