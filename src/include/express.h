#ifndef EXPRESS_H
#define EXPRESS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include "database.h"
using namespace std;
const int MAX_USER = 100;
enum LoginStatus {
    User_LOGIN_SUCCESS,
    Admin_LOGIN_SUCCESS,
    FAIL,
    NOT_FOUND
};

vector<int> read_packets();
string get_time();
void signup(AccountDatabase &account_db);
LoginStatus login(Account &user,AccountDatabase &account_db);
#endif
