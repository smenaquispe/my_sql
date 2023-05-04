#include<iostream>
#include<iomanip>
#include<fstream>
#include<cstring>
using namespace std;

void printTable(const char * fileName);

int main(int argc, char const *argv[])
{
    const char* fileName = "students";
    printTable(fileName);

    return 0;
}

void printTable(const char * tableName) {

    size_t lenBuffer = 1024;
    char buffer[lenBuffer];

    ifstream schemasFile("./db/schema");

    // print head of table (schema)
    if (schemasFile.is_open()) {
        int pos = 0;
        while (schemasFile.getline(buffer + pos, lenBuffer)) {
            char* token = strtok(buffer + pos, " # ");
            if(!strcmp(token,tableName)) {
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
        }
    } else {
        cout<<"Can't open file"<<"./db/schema"<<endl;
    }

    schemasFile.close();

    // print row of the table
    char fileName[256];
    strcpy(fileName, "./db/");
    strcat(fileName, tableName);
    ifstream tableFile(fileName);

    if (tableFile.is_open()) {
        int pos = 0;
        while (tableFile.getline(buffer + pos, lenBuffer)) {

            char* token = strtok(buffer + pos, " # ");
            while(token != nullptr) {
                cout<<setw(20)<<left<<token<<setw(20)<<right;
                token = strtok(nullptr, " # ");
            }
            cout<<endl;

            pos += tableFile.gcount();

            if(pos >= sizeof(buffer)) {
                pos = 0;
            }
        }
    } else {
        cout<<"Can't open file "<<tableName<<endl;
    }

    tableFile.close();
}