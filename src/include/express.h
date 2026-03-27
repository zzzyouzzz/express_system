#ifndef EXPRESS_H
#define EXPRESS_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int MAX_USER = 100;
enum LoginStatus {
    SUCCESS,
    FAIL,
    NOT_FOUND
};
enum AccountType {
    USER,
    ADMIN
};
int user_count = 0;
typedef class User {
private:

public:
    void Userloop();
}User;
typedef struct Account {
    int id;
    string name;
    string phone;
    string password;
    int balance;
    string address;
    AccountType type;
    Account();
    Account(int id, string name, string phone, string password, int balance, string address);
}Account;
Account accounts[MAX_USER];
Account signup();
int login(AccountType& user_out);
void init();
int logout();
#endif
