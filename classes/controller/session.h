#ifndef SESSION
#define SESSION

#include"dbController.h"

void DbController::init(char * input) {
    /* to join the session of megatron 3000 */
    regex pattern(this->init_pattern, regex_constants::icase);

    if (regex_match(input, pattern)) {
        if(this->inSession) cout<<"You've already stayed in MEGATRON3000\n";
        else {
            cout<<"Welcome to MEGATRON 3000 !\n";     
            this->inSession = true;
        }
    } 
}

void DbController::quit(char * input) {
    /** break the session but not quit the program */
    regex pattern(this->quit_pattern, regex_constants::icase);

    if (regex_match(input, pattern)){
        this->inSession = false;
    }
}

#endif