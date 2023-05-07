#ifndef CREATE_SCHEMA
#define CREATE_SCHEMA

#include"db.h"

void DB::createSchema() {

    ifstream schemasFile("./db/schema");
    ofstream tempSchemaFile("./db/tempSchema");
    ofstream columnsFile("./db/columns");

    FILE* inputColumnsFile = fopen("./db/input_columns", "r");
    char tempBuffer[1024];
    fgets(tempBuffer, 1024, inputColumnsFile);

    if(newSchemaName == NULL){
        setNewSchemaName(defaultName);
    }
    
    tempSchemaFile<<this->newSchemaName;

    if(schemasFile.is_open()) {
        int pos = 0;
        while (schemasFile.getline(this->buffer + pos, this->lenBuffer)) {
            char* token = strtok(this->buffer + pos, " # ");
            if(!strcmp(token,this->tableName)) {         

                columnsFile<<this->tableName<<" ";

                bool isType = false;
                while(token != nullptr) {
                    if(strcmp(token, this->tableName)) { // no guardar el nombre de la tabla
                        
                        if(isType) { // si es un tipo de datos
                            isType = false;
                            tempSchemaFile<<" # "<<token;
                        }

                        if(strstr(tempBuffer, token)) { // si token se encuentra en las columnas
                            isType = true;
                            tempSchemaFile<<" # "<<token;
                            columnsFile<<"1";

                        } else {
                            if(!isType)
                                columnsFile<<"0";
                        }
                    }
                    token = strtok(nullptr, " # ");
                } 
                break;
            }

            if(pos >= sizeof(this->buffer)) {
                pos = 0;
            }
        }   
    } else {
        cout<<"Can't open file"<<"./db/schema"<<endl;
    }
}

#endif