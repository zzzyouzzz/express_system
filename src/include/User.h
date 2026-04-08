#ifndef USER_H
#define USER_H
#include "express.h"
using namespace std;
class User{
    private:
        Account &account;
        PacketDatabase &packet_db;
        AccountDatabase &account_db;
    public:
        User( Account &account,PacketDatabase &packet_db,AccountDatabase &account_db) : account(account),packet_db(packet_db),account_db(account_db) {}
        int get_balance();
        Packet query_packet_by_tracking_number(int tracking_number);
        vector<Packet> query_packet_by_sender(string sender);
        vector<Packet> query_packet_by_receiver(string receiver);
        bool receive_packet(int tracking_number);
        bool send_packet(Packet pkt);
        void change_password(string new_password);
        void recharge(int amount);
        string get_name();
};
#endif
