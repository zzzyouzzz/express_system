#include "Courier.h"


bool Courier::collect_packet(string account_id, int tracking_number) {
    try {
        AccountInfo account = account_db.find(account_id);
        if (account.empty()) throw runtime_error("Account not found");
        if (account.type != AccountInfo::AccountType::courier) throw runtime_error("Account type is not Courier");
        Packet packet = packet_db.find(tracking_number);
        if (packet.empty()) throw runtime_error("Packet not found");
        bool isCollected = account_service.settleToCourier(account_id, packet.goods->get_price());
        if (!isCollected) throw runtime_error("Failed to settle to Courier");
        packet.status = Packet::PacketStatus::delivered;
        if (!packet_db.update("status", packet, tracking_number)) throw runtime_error("Failed to update packet status");
        account_db.commit();
        packet_db.commit();
        return true;
    } catch (const runtime_error &e) {
        account_db.rollback();
        packet_db.rollback();
        throw false;
    }
}

vector<Packet> Courier::query_packet(string account_id, const Packet& query_packet) {
    vector<Packet> result;
    if(query_packet.tracking_num != 0) {
        result.push_back(packet_db.find(query_packet.tracking_num));
    }
    else {
        result = packet_db.find("courier_id", account_id);
    }
    auto it = remove_if(result.begin(), result.end(), [&](Packet pkt) {
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
    result.erase(it, result.end());
    return result;
}
