#ifndef PRINT_TABLE
#define PRINT_TABLE

#include"db.h"

void DB::printTable() {
    printHeader(false);
    printBody();
}

void DB::printNewTable() {
    printHeader(true);
    createTable();
}

void DB::printHeader(bool newTable = false) {

    ofstream whereValueFile("./db/where_value");
    ifstream schemasFile;

    if(newTable) {
        schemasFile.open("./db/tempSchema");
        setTable(this->newSchemaName);
    } else {
        schemasFile.open("./db/schema");
    }

    if (schemasFile.is_open()) {
        int pos = 0;
        int count = 0;
        while (schemasFile.getline(this->buffer + pos, this->lenBuffer)) {
            char* token = strtok(this->buffer + pos, " # ");
            if(!strcmp(token,this->tableName)) {
                bool show = false;
                while(token != nullptr) {
                    if(show){
                        
                        if(whereValueFile && !strcmp(token, this->columnCompare)){ 
                            whereValueFile<<count<<endl;
                        }

                        cout<<setw(20)<<left<<token<<setw(20)<<right;
                        show = false;
                        count++;
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

void DB::printBody() {
    // print row of the table
    char fileName[256];

    strcpy(fileName, "./db/tables/");
    strcat(fileName, this->tableName);

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