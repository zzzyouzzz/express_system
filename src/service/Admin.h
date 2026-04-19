#ifndef ADMIN_H
#define ADMIN_H
#include "Account.h"
#include "time.h"
using namespace std;
class Admin : public Account {
    public:
        vector<Packet> query_packet(string account_id, const Packet& query_packet) override;
        bool assign_courier(int tracking_number, string courier_id) override;
        Admin(Database<int, Packet> &packet_db, Database<string, AccountInfo> &account_db) : Account(packet_db, account_db) {}
        bool send_packet(string account_id, string receiver, Item::ItemType item_type, string item_name) override {
            throw runtime_error("Admin cannot send packet");
            return false;
        }
        bool receive_packet(string account_id, int tracking_number) override {
            throw runtime_error("Admin cannot receive packet");
            return false;
        }
        bool recharge(string account_id, unsigned int amount) override {
            throw runtime_error("Admin cannot recharge");
            return false;
        }
        bool change_password(string account_id, string new_password) override {
            throw runtime_error("Admin cannot change password");
            return false;
        }
        bool collect_packet(string account_id, int tracking_number) override {
            throw runtime_error("Admin cannot collect packet");
            return false;
        }
};
#endif