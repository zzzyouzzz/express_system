#ifndef ADMIN_H
#define ADMIN_H
#include "database.h"
using namespace std;
class Admin {
    private:
        Account &account;
        PacketDatabase &packet_db;
        AccountDatabase &account_db;
    public:
        Admin(Account &account, PacketDatabase &packet_db, AccountDatabase &account_db) :account(account), packet_db(packet_db), account_db(account_db) {}
        ~Admin() {}
        vector<Packet> query_packet_by_sender(string sender);
        vector<Packet> query_packet_by_receiver(string receiver);
        Account query_account(string username);
        string get_name();
};
#endif