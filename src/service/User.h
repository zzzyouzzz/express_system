#ifndef USER_H
#define USER_H
#include "Account.h"
#include "time.h"

class User : public Account {
    public:
        bool receive_packet(string account_id, int tracking_number) override;
        bool send_packet(string account_id, string receiver, Item::ItemType item_type, string item_name) override;
        bool change_password(string account_id, string new_password) override;
        bool recharge(string account_id, unsigned int amount) override;
        vector<Packet> query_packet(string account_id, const Packet& query_packet) override;
        User(Database<int, Packet> &packet_db, Database<string, AccountInfo> &account_db) : Account(packet_db, account_db) {}
        bool assign_courier(int tracking_number, string courier_id) override {
            throw runtime_error("User cannot assign courier");
            return false;
        }
        bool collect_packet(string account_id, int tracking_number) override {
            throw runtime_error("User cannot collect packet");
            return false;
        }
        
};
#endif