#ifndef PARSE_CLAUSE
#define PARSE_CLAUSE

#include"dbController.h"


bool equal_op(char * param, char * value) {
    return (!strcmp(param, value));
}

bool higher_than(char * param, char * value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ > value_);
}

bool lower_than(char * param, char * value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ < value_);
}

bool higher_equal_than(char * param, char * value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ >= value_);
}

bool lower_equal_than(char * param, char * value) {
    int param_ = stoi(param);
    int value_ = stoi(value);
    return (param_ <= value_);
}


void DbController::parseClause(char * clause) {
    regex pattern(this->clause_pattern);
    smatch match;

    string c = string(clause);

    if (regex_search(c, match, pattern)) {
        db->setColumnCompare(strdup(match[1].str().c_str()));
        db->setValueCompare(strdup(match[3].str().c_str()));

        char * operator_ = strdup(match[2].str().c_str());

        if (!strcmp(operator_,"=")) {
            db->setCondition(equal_op);
            return;
        } else if (!strcmp(operator_,">")) {
            db->setCondition(higher_than);
            return;
        } else if (!strcmp(operator_,"<")) {
            db->setCondition(lower_than);
            return;
        } else if (!strcmp(operator_,">=")) {
            db->setCondition(higher_equal_than);
            return;
        } else if (!strcmp(operator_,"<=")) {
            db->setCondition(lower_equal_than);
            return;
        }
    } else {
        cout << "[Error] Syntax error in WHERE clause" << endl;
        return;
    }     
}

#endif