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
        string save_filename;
    public:
        AccountDatabase(string filename);
        ~AccountDatabase() {}
        bool add(Account account);
        Account* get_by_id(int id);
        Account* get_by_username(string username);
        bool remove(int id);
        bool update(Account account);
};
class PacketDatabase {
    private:
        map<int, Packet> packets;
        map<string, int> idx_sender;
        map<string, int> idx_receiver;
        string save_filename;
    public:
        PacketDatabase(string filename);
        ~PacketDatabase() {}
        bool add(Packet packet);
        Packet* get_by_id(int id);
        Packet* get_by_sender(string sender);
        Packet* get_by_receiver(string receiver);
        bool remove(int id);
        bool update(Packet packet);
};
#endif
