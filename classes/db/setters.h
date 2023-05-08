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

void DB::setColumnCompare(char * columnCompare) {
    this->columnCompare = columnCompare;
}

void DB::setValueCompare(char * valueCompare) {
    this->valueCompare = valueCompare;
}

void DB::setCondition(bool (*condition)(char *, char *)) {
    this->condition = condition;
}

#endif