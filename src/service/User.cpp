#include "User.h"

bool User::change_password(string account_id, string new_password) {
    try {
        AccountInfo account = account_db.find(account_id);
        bool updateOK = account_db.update("password", account, account.username);
        if(!updateOK) throw "error:failed to update password";
        account_db.commit();
        return true;
    } catch (...) {
        account_db.rollback();
        return false;
    }
}

bool User::recharge(string account_id, unsigned int amount) {
    try {
        AccountInfo account = account_db.find(account_id);
        bool updateOK = account_service.recharge(account_id, amount);
        if(!updateOK) throw "error:failed to recharge";
        account_db.commit();
        return true;
    } catch (...) {
        account_db.rollback();
        return false;
    }
}


bool User::send_packet(string account_id, string receiver, Item::ItemType item_type, string item_name) {
    AccountInfo account = account_db.find(account_id);
    Item *item;
    switch (item_type) {
        case Item::ItemType::commonItem:
            item = new CommonItem(item_name);
            break;
        case Item::ItemType::fragileItem:
            item = new FragileItem(item_name);
            break;
        case Item::ItemType::bookItem:
            item = new BookItem(item_name);
            break;
        default:
            cout<<"error:item type not supported"<<endl;
            return false;
    }
    try {
        bool transferOK = account_service.deductionForSendExpress(account.username, item->get_price());
        if (!transferOK) throw "error:insufficient balance";

        Packet packet;
        packet.sender = account.username;
        packet.receiver = receiver;
        packet.send_time = get_time();
        packet.receive_time = "----";
        packet.goods = item;
        packet.status = Packet::PacketStatus::pending;
        packet.tracking_num = packet_db.size() + 1;
        packet.courier_id = "";
        packet_db.insert(packet, packet.tracking_num);
        account_db.commit();
        packet_db.commit();
        return true;
    } catch (...) {
        account_db.rollback();
        packet_db.rollback();
        return false;
    }
}

bool User::receive_packet(string account_id, int tracking_number) {
    AccountInfo account = account_db.find(account_id);
    try {
        Packet pkt = packet_db.find(tracking_number);
        if(pkt.empty()) throw "error:packet not found";
        if(pkt.receiver != account.username) throw "error:packet not sent to you";
        if(pkt.status == Packet::PacketStatus::pending) throw "error:packet not delivered";
        if(pkt.status == Packet::PacketStatus::settled) throw "error:packet already received";
        pkt.status = Packet::PacketStatus::delivered;
        bool collectOK = packet_db.update("status", pkt, tracking_number);
        if(!collectOK) throw "error:failed to collect express";
        packet_db.commit();
        return true;
    } catch (...) {
        packet_db.rollback();
        return false;
    }
}

vector<Packet> User::query_packet(string account_id, const Packet& query_packet) {
        AccountInfo account = account_db.find(account_id);
        vector<Packet> packets;
        if(query_packet.tracking_num != 0) packets.push_back(packet_db.find(query_packet.tracking_num));
        else {
            vector<Packet> tmp = packet_db.find("sender", account.username);
            packets = packet_db.find("receiver", account.username);
            packets.insert(packets.end(), tmp.begin(), tmp.end());
        }
        auto it = remove_if(packets.begin(), packets.end(), [&](Packet pkt) {
            bool isMatch = true;
            if (query_packet.sender != "") {
                isMatch &= pkt.sender == query_packet.sender;
            }
            if (query_packet.receiver != "") {
                isMatch &= pkt.receiver == query_packet.receiver;
            }
            if (query_packet.status != Packet::PacketStatus::other) {
                isMatch &= pkt.status == query_packet.status;
            }
            if (query_packet.send_time != "") {
                isMatch &= pkt.send_time == query_packet.send_time;
            }
            if (query_packet.receive_time != "") {
                isMatch &= pkt.receive_time == query_packet.receive_time;
            }
            return !isMatch;
        });
        packets.erase(it, packets.end());
        return packets;
}