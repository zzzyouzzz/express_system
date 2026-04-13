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
        if(idx_sender.count(packet.sender) == 0){
            idx_sender[packet.sender] = {packet.tracking_number};
        }
        else{
            idx_sender[packet.sender].push_back(packet.tracking_number);
        }
        if(idx_receiver.count(packet.receiver) == 0){
            idx_receiver[packet.receiver] = {packet.tracking_number};
        }
        else{
            idx_receiver[packet.receiver].push_back(packet.tracking_number);
        }
        if(idx_send_time.count(packet.send_time) == 0){
            idx_send_time[packet.send_time] = {packet.tracking_number};
        }
        else{
            idx_send_time[packet.send_time].push_back(packet.tracking_number);
        }
        if(idx_receive_time.count(packet.receive_time) == 0){
            idx_receive_time[packet.receive_time] = {packet.tracking_number};
        }
        else{
            idx_receive_time[packet.receive_time].push_back(packet.tracking_number);
        }
    }
    file.close();
    save_filename = filename;
}
bool PacketDatabase::add(Packet packet) {
    if(packets.count(packet.tracking_number) > 0) return false;
    packets[packet.tracking_number] = packet;
    if(idx_sender.count(packet.sender) == 0){
        idx_sender[packet.sender] = {packet.tracking_number};
    }
    else{
        idx_sender[packet.sender].push_back(packet.tracking_number);
    }
    if(idx_receiver.count(packet.receiver) == 0){
        idx_receiver[packet.receiver] = {packet.tracking_number};
    }
    else{
        idx_receiver[packet.receiver].push_back(packet.tracking_number);
    }
    if(idx_send_time.count(packet.send_time) == 0){
        idx_send_time[packet.send_time] = {packet.tracking_number};
    }
    else{
        idx_send_time[packet.send_time].push_back(packet.tracking_number);
    }
    if(idx_receive_time.count(packet.receive_time) == 0){
        idx_receive_time[packet.receive_time] = {packet.tracking_number};
    }
    else{
        idx_receive_time[packet.receive_time].push_back(packet.tracking_number);
    }
    return true;
}
Packet PacketDatabase::get_by_id(int id) {
    if(packets.count(id) == 0) return Packet();
    return packets[id];
}
vector<Packet> PacketDatabase::get_by_sender(string sender) {
    if(idx_sender.count(sender) == 0) return {};
    vector<Packet> res;
    for(int id : idx_sender[sender]){
        res.push_back(packets[id]);
    }
    return res;
}
vector<Packet> PacketDatabase::get_by_receiver(string receiver) {
    if(idx_receiver.count(receiver) == 0) return {};
    vector<Packet> res;
    for(int id : idx_receiver[receiver]){
        res.push_back(packets[id]);
    }
    return res;
}
vector<Packet> PacketDatabase::get_by_send_time(string send_time) {
    if(idx_send_time.count(send_time) == 0) return {};
    vector<Packet> res;
    for(int id : idx_send_time[send_time]){
        res.push_back(packets[id]);
    }
    return res;
}
vector<Packet> PacketDatabase::get_by_receive_time(string receive_time) {
    if(idx_receive_time.count(receive_time) == 0) return {};
    vector<Packet> res;
    for(int id : idx_receive_time[receive_time]){
        res.push_back(packets[id]);
    }
    return res;
}
bool PacketDatabase::remove(int id) {
    if(packets.count(id) == 0) return false;
    Packet packet = packets[id];
    idx_sender.erase(packet.sender);
    idx_receiver.erase(packet.receiver);
    idx_send_time.erase(packet.send_time);
    idx_receive_time.erase(packet.receive_time);
    packets.erase(id);
    return true;
}
bool PacketDatabase::update(Packet packet) {
    if(packets.count(packet.tracking_number) == 0) return false;
    Packet old_packet = packets[packet.tracking_number];
    if(old_packet.sender!=packet.sender){
        vector<int> &ids = idx_sender[old_packet.sender];
        ids.erase(std::remove(ids.begin(), ids.end(), packet.tracking_number), ids.end());
        idx_sender[packet.sender].push_back(packet.tracking_number);
    }
    if(old_packet.receiver!=packet.receiver){
        vector<int> &ids = idx_receiver[old_packet.receiver];
        ids.erase(std::remove(ids.begin(), ids.end(), packet.tracking_number), ids.end());
        idx_receiver[packet.receiver].push_back(packet.tracking_number);
    } 
    if(old_packet.send_time!=packet.send_time){
        vector<int> &ids = idx_send_time[old_packet.send_time];
        ids.erase(std::remove(ids.begin(), ids.end(), packet.tracking_number), ids.end());
        idx_send_time[packet.send_time].push_back(packet.tracking_number);
    }
    if(old_packet.receive_time!=packet.receive_time){
        vector<int> &ids = idx_receive_time[old_packet.receive_time];
        ids.erase(std::remove(ids.begin(), ids.end(), packet.tracking_number), ids.end());
        idx_receive_time[packet.receive_time].push_back(packet.tracking_number);
    }
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