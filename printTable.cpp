#ifndef PRINT_TABLE
#define PRINT_TABLE

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void printTable(const vector<string>& head, const vector< vector<string> >& body) {

    for(const string column : head) {
        cout<<left<<setw(10)<<column;
    }

    cout<<endl;

    cout<<setfill('-')<<setw(head.size() * 10)<<"-"<<endl;
    cout<<setfill(' ') ;

    // Imprime los datos de cada fila
    for (const vector<string> row : body) {
        for(const string prop : row) {
            cout<<setfill(' ')<<left<<setw(10)<<prop;
        }

        cout<<endl;
    }
}

#endif