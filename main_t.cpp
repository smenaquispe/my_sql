#include<iostream>
#include<regex>

#include"classes/db/db.h"

using namespace std;

bool isOpen = true;
bool inSession = false;

void init(char * input);
void quit(char * input);
void select(char * input, DB & db);

int main() {

    size_t lenInput = 256;
    char input[lenInput];

    // create db controller
    DB db;

    do{
        if(!inSession) cout<<"% ";
        else cout<<"> ";

        cin.getline(input, lenInput);
 
        if(input == "\n") continue;

        init(input);
        quit(input);

        if(inSession) {
            if(input[0] == '&')
                select(input, db);
        }

    } while(isOpen);

    return 0;
}

/* to join the session of megatron 3000 */
void init(char * input) {
    regex pattern("MEGATRON3000", regex_constants::icase);
    if (regex_match(input, pattern)) {
        if(inSession) cout<<"You've already stayed in MEGATRON3000\n";
        else {
            cout<<"Welcome to MEGATRON 3000 !\n";     
            inSession = true;
        }
    } 
}

/** break the session but not quit the program */
void quit(char * input) {
    regex pattern("QUIT", regex_constants::icase);
    if (regex_match(input, pattern)){
        inSession = false;
    }
}

// select funciont 
void select(char * input, DB & db) {

    regex select_pattern("& SELECT (.*) FROM (.*) #",regex_constants::icase);
    smatch match;

    // Intentamos buscar la cláusula SELECT
    string strInput = string(input);
    if (regex_search(strInput, match, select_pattern)) {

        char * columnNames = strdup(match[1].str().c_str());
        char * tableName = strdup(match[2].str().c_str());

        db.setTable(tableName);

        // select all
        if(!strcmp(columnNames, "*")) db.printTable();

        // select column names
        else {
            db.setColumns(columnNames);
            db.saveColumns();
        }

        free(columnNames);
        free(tableName);
    }
}