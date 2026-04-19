#ifndef EXPRESS_H
#define EXPRESS_H
#include <string>
#include "Item.h"

using namespace std;
struct Packet {
    enum PacketStatus{
        pending,
        delivered,
        settled,
        other
    };
    int tracking_num;
    string sender;
    string receiver;
    string send_time;
    string receive_time;
    PacketStatus status;
    Item *goods;
    string courier_id;
    Packet() : tracking_num(0), status(other), sender(""), receiver(""), send_time(""), receive_time(""), courier_id("") {
        goods = nullptr;
    }
    bool empty() {
        return tracking_num == 0;
    }
};
#endif