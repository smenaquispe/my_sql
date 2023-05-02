#include<iostream>
#include<vector>
#include<regex>
#include<string>
#include"split.cpp"
#include"findSchema.cpp"
#include"readTable.cpp"
#include"printTable.cpp"
#include"isSubset.cpp"
#include"findPositions.cpp"
#include"saveTable.cpp"

/**
 * 
 * 1. SELECT * FROM `table`
 * 2. SELECT `...props` FROM `table`
 * 3. SELECT * FROM `table` | `file`
 * 4. INNER JOIN
*/

/**
 * db/schema -> firma de las tablas
 * 
*/

using namespace std;

bool isOpen = true;
bool inSession = false;


void init(string);
void quit(string);
void select(string);

bool equal_op(string param, string value) {
    return (param == value);
}

bool higher_than(string param, string value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ > value_);
}

bool lower_than(string param, string value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ < value_);
}

bool higher_equal_than(string param, string value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ >= value_);
}

bool lower_equal_than(string param, string value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ <= value_);
}

int main(int argc, char const *argv[])
{
    string input; 

    while (isOpen)
    {
        if(!inSession) cout<<"% ";
        else cout<<"> ";

        getline(cin, input);

        if(input == "\n") continue;

        init(input);
        quit(input);

        if(inSession) {
            if(input[0] == '&')
                select(input);
        }

    }
    
    return 0;
}

/* to join the session of megatron 3000 */
void init(string input) {
    if(input == "MEGATRON3000" || input == "megatron3000" || input == "Megatron3000")  {
        if(inSession) cout<<"You've already stayed in MEGATRON3000\n";
        else {
            cout<<"Welcome to MEGATRON 3000 !\n";     
            inSession = true;
        }
    } 
}

/** break the session but not quit the program */
void quit(string input) {
    if(input == "quit" || input == "QUIT" || input == "Quit") 
        inSession = false;
}


void select(string input) {
    // Expresión regular para la cláusula SELECT
    regex select_pattern("& SELECT (.*) FROM (.*) #",regex_constants::icase);

    // Expresión regular para la cláusula WHERE
    regex where_pattern("& SELECT (.*) FROM (.*) WHERE (.*) #",regex_constants::icase);

    regex save_pattern("& SELECT (.*) FROM (.*) WHERE (.*) \\| (.*) #",regex_constants::icase);


    smatch match;
    smatch match3;
    smatch match4;

    // Intentamos buscar la cláusula SELECT
    if (regex_search(input, match, select_pattern)) {
        // Parseamos los nombres de columna y tabla
        string columnNames = match[1].str();
        string nameTable = match[2].str();

        // Parseamos la cláusula WHERE, si existe
        string clause;
        if (regex_search(input, match3, where_pattern)) {
            nameTable = match3[2].str();
            clause = match3[3].str();
        }

        /* si se necesita del otro operador para guardar */
        string fileName;
        if (regex_search(input, match4, save_pattern)) {
            clause = match4[3].str();
            fileName = match4[4].str();
        }

        // Obtenemos el esquema de la tabla
        vector<string> head = findSchema(nameTable);

        if (head.size() == 0) {
            cout << "[Error] Can't find the schema: " << nameTable << endl;
            return;
        }

        // Vector de columnas a mostrar
        vector<string> columns;
        
        if (columnNames == "*") {
            columns = head;
        } else {
            // Parseamos los nombres de columna
            columns = splitString(columnNames, ',');
            // Verificamos que todas las columnas existan en el esquema
            if (!isSubset(columns, head)) {
                cout << "[Error] Can't find some columns in the schema: " << nameTable << endl;
                return;
            }
        }

        // Vector de posiciones de las columnas en la tabla
        vector<int> positions = findPositions(columns, head);

        // Llamamos a la función readTable con o sin cláusula WHERE, según corresponda
        vector<vector<string>> body;
        if (clause.empty()) {
            body = readTable(nameTable, positions);
        } else {
            // Parseamos la cláusula WHERE
            regex clause_pattern(R"((\w+)\s*([><=!]+)\s*(\w+))");
            smatch match2;
            if (regex_search(clause, match2, clause_pattern)) {
                string column = match2[1].str();
                string operator_ = match2[2].str();
                string value = match2[3].str();

                bool (*condition)(string, string);

                if (operator_ == "=") {
                    condition = equal_op;
                } else if (operator_ == ">") {
                    condition = higher_than;
                } else if (operator_ == "<") {
                    condition = lower_than;
                } else if (operator_ == ">=") {
                    condition = higher_equal_than;
                } else if (operator_ == "<=") {
                    condition = lower_equal_than;
                }

                if(!isSubset({column}, head)) {
                    cout << "[Error] Syntax error in WHERE clause" << endl;
                    return;
                }

                int column_position = findPositions({column}, head)[0];
                body = readTable(nameTable, column_position, condition, value, positions);
            } else {
                cout << "[Error] Syntax error in WHERE clause" << endl;
                return;
            }
        }

        if(fileName.length() > 0) {
            vector<string> headSchema = findSchema(columns, nameTable);
            saveTable(fileName, headSchema, body);
        }

        // Imprimimos la tabla resultante
        printTable(columns, body);

    } else 
        cout << "[Error] Syntax error" <<endl;
}