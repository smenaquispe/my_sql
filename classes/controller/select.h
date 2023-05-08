#ifndef SELECT
#define SELECT

#include"dbController.h"

// select funciont 
void DbController::select(char * input) {

    regex pattern(this->select_pattern,regex_constants::icase);
    regex pattern2(this->select_where_pattern,regex_constants::icase);
    smatch match;

    char * columnNames;
    char * tableName;
    char * clause;

    // Intentamos buscar la cláusula SELECT
    string strInput = string(input);
    if (regex_search(strInput, match, pattern)) {
        
        columnNames = strdup(match[1].str().c_str());
        tableName = strdup(match[2].str().c_str());

        // where clause
        if(regex_search(strInput, match, pattern2)) {
            clause = strdup(match[3].str().c_str());
            this->parseClause(clause);
            return;
        }
    } else {
        return;
    }

    db->setTable(tableName);

    // select all
    if(!strcmp(columnNames, "*")) db->printTable();

    // select column names
    else {
        db->setColumns(columnNames);
        db->saveColumns();
        db->createSchema();
        db->createTable();
        db->printNewTable();
    }

    free(columnNames);
    free(tableName);
    free(clause);
}

#endif