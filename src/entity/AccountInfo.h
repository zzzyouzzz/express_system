#ifndef ACCOUNT_INFO_H
#define ACCOUNT_INFO_H
#include <string>
using namespace std;
struct AccountInfo {
    enum AccountType{
        user,
        courier,
        admin
    };
    string username;
    string password;
    string name;
    string phone;
    string address;
    double balance;
    AccountType type;

    AccountInfo() : username("") {}
    bool empty() const {
        return username.empty();
    };
};
#endif