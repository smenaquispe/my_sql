#ifndef SELECT
#define SELECT

#include"dbController.h"

// select funciont 
void DbController::select(char * input) {

    regex pattern(this->select_pattern,regex_constants::icase);
    smatch match;
    // Intentamos buscar la cláusula SELECT
    string strInput = string(input);
    if (regex_search(strInput, match, pattern)) {

        char * columnNames = strdup(match[1].str().c_str());
        char * tableName = strdup(match[2].str().c_str());

        db->setTable(tableName);

        // select all
        if(!strcmp(columnNames, "*")) db->printTable();

        // select column names
        else {
            db->setColumns(columnNames);
            db->saveColumns();
            db->createSchema();
        }

        free(columnNames);
        free(tableName);
    }
}

#endif