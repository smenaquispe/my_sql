#ifndef DB_CONTROLLER
#define DB_CONTROLLER

#include"../db/db.h"
#include<regex>

class DbController
{
    private:
        DB * db;
        const char * init_pattern = "MEGATRON3000";
        const char * quit_pattern = "QUIT";
        const char * select_pattern = "& SELECT (.*) FROM (.*) #";

    public:
        bool inSession;

        DbController(DB * db);
        ~DbController();

        void init(char * input);
        void quit(char * input);
        void select(char * input);
};

DbController::DbController(DB * db)
{
    this->db = db;
    this->inSession = false;
}

DbController::~DbController()
{
}

#include"session.h"
#include"select.h"

#endif