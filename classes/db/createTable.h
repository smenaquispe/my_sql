#ifndef CREATE_TABLE
#define CREATE_TABLE

#include"db.h"

void DB::createTable() {

    ifstream columnsFile("./db/columns");
    char table[128];
    char columns[128];

    if(columnsFile.is_open()) {
        int pos = 0;
        while(columnsFile.getline(this->buffer + pos, this->lenBuffer)) {
            char * token = strtok(this->buffer + pos, " ");
            strcpy(table, token);
            token = strtok(nullptr, " ");
            strcpy(columns, token);
        }
    }

    char fileName[256];
    strcpy(fileName, "./db/tables/");
    strcat(fileName, table);
    ifstream tableFile(fileName);
    ofstream tempTableFile("./db/tempTable");

    if(tableFile.is_open()) {
        int pos = 0;
        while (tableFile.getline(this->buffer + pos, this->lenBuffer))
        {
            
            // una linea
            char* token = strtok(this->buffer + pos, " # ");
            int pos_column = 0;
            bool first = true;
            while(token != nullptr) {

                if(columns[pos_column] - '0') { // si es 1
                    if(!first) {
                        tempTableFile<<" # ";
                    } else {
                        first = false;
                    }
                    tempTableFile<<token;
                }


                pos_column += 2;
                token = strtok(nullptr, " # ");
            }

            tempTableFile<<endl;

            pos += tableFile.gcount();

            if(pos >= sizeof(this->buffer)) {
                pos = 0;
            }
        }
        
    }
}

#endif