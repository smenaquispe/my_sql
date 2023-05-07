#ifndef PRINT_TABLE
#define PRINT_TABLE

#include"db.h"

void DB::printTable() {
    printHeader(false);
    printBody(false);
}

void DB::printNewTable() {
    printHeader(true);
    printBody(true);
}

void DB::printHeader(bool newTable = false) {

    ifstream schemasFile;

    if(newTable) {
        schemasFile.open("./db/tempSchema");
        setTable(this->newSchemaName);
    } else {
        schemasFile.open("./db/schema");
    }

    if (schemasFile.is_open()) {
        int pos = 0;
        while (schemasFile.getline(this->buffer + pos, this->lenBuffer)) {
            char* token = strtok(this->buffer + pos, " # ");
            if(!strcmp(token,this->tableName)) {
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

            if(pos >= sizeof(this->buffer)) {
                pos = 0;
            }
        }
    } else {
        cout<<"Can't open file"<<"./db/schema"<<endl;
    }

    schemasFile.close();
}

void DB::printBody(bool newTable = false) {
    // print row of the table
    char fileName[256];

    if(newTable) {
        strcpy(fileName, "./db/tempTable");
    }else {
        strcpy(fileName, "./db/tables/");
        strcat(fileName, this->tableName);
    }

    ifstream tableFile(fileName);

    if (tableFile.is_open()) {
        int pos = 0;
        while (tableFile.getline(this->buffer + pos, this->lenBuffer)) {

            char* token = strtok(this->buffer + pos, " # ");
            while(token != nullptr) {
                cout<<setw(20)<<left<<token;
                token = strtok(nullptr, " # ");
            }
            cout<<endl;

            pos += tableFile.gcount();

            if(pos >= sizeof(this->buffer)) {
                pos = 0;
            }
        }
    } else {
        cout<<"Can't open file "<<this->tableName<<endl;
    }

    tableFile.close();
}


#endif