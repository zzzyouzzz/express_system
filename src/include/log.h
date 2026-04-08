#ifndef LOG_H
#define LOG_H
#include "database.h"
using namespace std;
enum LoginStatus {
    User_LOGIN_SUCCESS,
    Admin_LOGIN_SUCCESS,
    FAIL,
    NOT_FOUND
};
void signup(AccountDatabase &account_db);
LoginStatus login(Account &user,AccountDatabase &account_db);
#endif
