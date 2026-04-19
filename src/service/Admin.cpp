#include "Admin.h"

vector<Packet> Admin::query_packet(string account_id, const Packet& query_packet) {
    vector<Packet> result;
    if(query_packet.tracking_num != 0) {
        result.push_back(packet_db.find(query_packet.tracking_num));
    }
    else {
        result = packet_db.findall();
    }

    auto it = std::remove_if(result.begin(), result.end(), [&](Packet pkt) {
        bool isMatch = true;
        if (query_packet.sender != "") {
            isMatch &= (pkt.sender == query_packet.sender);
        }
        if (query_packet.receiver != "") {
            isMatch &= (pkt.receiver == query_packet.receiver);
        }
        if (query_packet.status != Packet::PacketStatus::other) {
            isMatch &= (pkt.status == query_packet.status);
        }
        if (query_packet.courier_id == "assign") {
            isMatch &= (pkt.courier_id == "");
        }
        return !isMatch;
    });
    result.erase(it, result.end());
    return result;
}

bool Admin::assign_courier(int tracking_number, string courier_id) {
    try {
        Packet pkt = packet_db.find(tracking_number);
        if(pkt.empty()) throw runtime_error("Packet not found");
        if(pkt.status != Packet::pending) throw runtime_error("Packet status is not pending");
        pkt.courier_id = courier_id;
        if(!packet_db.update("courier_id", pkt, tracking_number)) throw runtime_error("Failed to update packet with courier_id");
        packet_db.commit();
        return true;
    } catch(const runtime_error &e) {
        packet_db.rollback();
        return false;
    }
}
