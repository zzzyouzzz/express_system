#include "database.h"

PacketDatabase::PacketDatabase(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << filename << endl;
        return;
    }
    int count;
    file >> count;
    for (int i = 0; i < count; i++) {
        Packet packet;
        int status;
        file >> packet.tracking_number >> packet.sender >> packet.receiver >> packet.send_time >> packet.receive_time >> status >> packet.content;
        packet.status = (PacketStatus)status;
        packets[packet.tracking_number] = packet;
        idx_sender[packet.sender] = packet.tracking_number;
        idx_receiver[packet.receiver] = packet.tracking_number;
    }
    file.close();
    save_filename = filename;
}
bool PacketDatabase::add(Packet packet) {
    if(packets.count(packet.tracking_number) > 0) return false;
    packets[packet.tracking_number] = packet;
    idx_sender[packet.sender] = packet.tracking_number;
    idx_receiver[packet.receiver] = packet.tracking_number;
    return true;
}
Packet* PacketDatabase::get_by_id(int id) {
    if(packets.count(id) == 0) return nullptr;
    return &packets[id];
}
Packet* PacketDatabase::get_by_sender(string sender) {
    if(idx_sender.count(sender) == 0) return nullptr;
    return &packets[idx_sender[sender]];
}
Packet* PacketDatabase::get_by_receiver(string receiver) {
    if(idx_receiver.count(receiver) == 0) return nullptr;
    return &packets[idx_receiver[receiver]];
}
bool PacketDatabase::remove(int id) {
    if(packets.count(id) == 0) return false;
    Packet packet = packets[id];
    idx_sender.erase(packet.sender);
    idx_receiver.erase(packet.receiver);
    packets.erase(id);
    return true;
}
bool PacketDatabase::update(Packet packet) {
    if(packets.count(packet.tracking_number) == 0) return false;
    Packet old_packet = packets[packet.tracking_number];
    idx_sender.erase(old_packet.sender);
    idx_receiver.erase(old_packet.receiver);
    idx_sender[packet.sender] = packet.tracking_number;
    idx_receiver[packet.receiver] = packet.tracking_number;
    packets[packet.tracking_number] = packet; 
    return true;
}
PacketDatabase::~PacketDatabase() {
    ofstream file(save_filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << save_filename << endl;
        return;
    }
    file << packets.size() << endl;
    for (auto& packet : packets) {
        file << packet.second.tracking_number << " " << packet.second.sender << " " << packet.second.receiver << " " << packet.second.send_time << " " << packet.second.receive_time << " " << (int)packet.second.status << " " << packet.second.content << endl;
    }
    file.close();
}