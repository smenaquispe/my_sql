#ifndef SAVE_COLUMNS
#define SAVE_COLUMNS

#include"db.h"

void DB::saveColumns() {
    char * columns = this->columnsSelected;
    char * token = strtok(columns, ",");

    ofstream file("./db/columns");

    file<<this->tableName;
    while (token != nullptr)
    {
        file<<" # ";
        file<<string(token).substr(string(token).find_first_not_of(" "), string(token).find_last_not_of(" ") + 1);
        token = strtok(nullptr, ",");
    } 
              
    file.close();
}


#endif