#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "dao/database.h"
#include "AccountService.h"
#include "entity/Packet.h"
#include "entity/Item.h"
class Account{
    protected:
        Database<int, Packet> &packet_db;
        Database<string, AccountInfo> &account_db;
        AccountService account_service;
    public:
        Account(Database<int, Packet> &packet_db, Database<string, AccountInfo> &account_db) : packet_db(packet_db), account_db(account_db), account_service(account_db) {}
        int get_balance(string account_id) {
            return account_db.find(account_id).balance;
        }
        string get_name(string account_id) {
            return account_db.find(account_id).name;
        }
        virtual bool receive_packet(string account_id, int tracking_number) = 0;
        virtual bool send_packet(string account_id, string receiver, Item::ItemType item_type, string item_name) = 0;
        virtual bool change_password(string account_id, string new_password) = 0;
        virtual bool recharge(string account_id, unsigned int amount) = 0;
        virtual bool assign_courier(int tracking_number, string courier_id) = 0;
        virtual bool collect_packet(string account_id, int tracking_number) = 0;
        virtual vector<Packet> query_packet(string account_id, const Packet& query_packet) = 0;
};
#endif