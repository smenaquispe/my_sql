#ifndef SAVE_TABLE
#define SAVE_TABLE

#include<vector>
#include<iostream>
#include<fstream>

using namespace std;

void saveTable(string fileName, vector<string> columns, vector< vector<string> > body) {
    string schema = fileName;
    for(const string c : columns) {
        schema += " # " + c;
    }

    ofstream file("./db/schema", ios::app);
    if (!file.is_open()) {
        cout<<"Error: no se pudo abrir el archivo."<<endl;
        return;
    }
    file<<schema<<endl;
    file.close();

    string table = "";

    int numberRow = 0;
    for(const vector<string> row : body) {

        int numberAttr = 0;

        for(const string attr : row) {
            table += attr;
            if(numberAttr != row.size() - 1) {
                table += " # ";
            }
            numberAttr++;
        }

        if(numberRow != body.size() - 1) {
            table += "\n";
        }

        numberRow++;
    }

    ofstream outfile("./db/" + fileName); // Crear archivo
    if (outfile.is_open()) { // Verificar si se abrió correctamente
        outfile << table; // Escribir en el archivo
        outfile.close(); // Cerrar el archivo
    }
    else {
       cout << "Error al crear el archivo." <<endl; // Mensaje en consola
    }
    
}

#endif