#ifndef DATABASE_H
#define DATABASE_H
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <fstream>
using namespace std;
enum PacketStatus {
    SENT,
    RECEIVED
};
enum AccountType {
    USER,
    ADMIN
};
struct Account{
    int id;
    string username;
    string password;
    string name;
    string phone;
    string address;
    double balance;
    AccountType type;
};
struct Packet{
    int tracking_number;
    string sender;
    string receiver;
    string send_time;
    string receive_time;
    PacketStatus status;
    string content;
};
class AccountDatabase {
    private:
        map<int, Account> accounts;
        map<string, int> idx_username;
    public:
        AccountDatabase(string filename);
        ~AccountDatabase() {}
        void add(Account account);
        Account* get_by_id(int id);
        Account* get_by_username(string username);
        void save();
        void remove(int id);
        void update(Account account);
};

#endif
