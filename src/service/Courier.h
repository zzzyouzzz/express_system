#pragma once
#include "service/Account.h"
#include "entity/AccountInfo.h"

class Courier : public Account {
    public:
        bool collect_packet(string account_id, int tracking_number) override;
        vector<Packet> query_packet(string account_id, const Packet& query_packet) override;
        Courier(Database<int, Packet> &packet_db, Database<string, AccountInfo> &account_db) : Account(packet_db, account_db) {}
        bool assign_courier(int tracking_number, string courier_id) override {
            throw runtime_error("Courier cannot assign courier");
            return false;
        }
        bool send_packet(string account_id, string receiver, Item::ItemType item_type, string item_name) override {
            throw runtime_error("Courier cannot send packet");
            return false;
        }
        bool receive_packet(string account_id, int tracking_number) override {
            throw runtime_error("Courier cannot receive packet");
            return false;
        }
        bool recharge(string account_id, unsigned int amount) override {
            throw runtime_error("Courier cannot recharge");
            return false;
        }
        bool change_password(string account_id, string new_password) override {
            throw runtime_error("Courier cannot change password");
            return false;
        }
};