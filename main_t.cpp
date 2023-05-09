#include<iostream>
#include<regex>

#include"classes/db/db.h"
#include"classes/controller/dbController.h"

using namespace std;

bool isOpen = true;

int main() {

    size_t lenInput = 256;
    char input[lenInput];

    // create db controller
    DB * db = new DB;
    DbController controller(db);

    do{
        if(!controller.inSession) cout<<"% ";
        else cout<<"> ";

        cin.getline(input, lenInput);
 
        if(input == "\n") continue;

        controller.init(input);
        controller.quit(input);

        if(controller.inSession) {
            if(input[0] == '&') {
                controller.select(input);
            }
        }

    } while(isOpen);


    delete db;

    return 0;
}
