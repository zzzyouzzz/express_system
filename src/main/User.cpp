#include "User.h"
#include "express.h"
int User::get_balance() {
    return account.balance;
}
Packet User::query_packet_by_tracking_number(int tracking_number) {
    Packet pkt = packet_db.get_by_id(tracking_number);
    if(pkt.receiver != account.name||pkt.sender != account.name){
        cout<<"error:packet not sent to you"<<endl;
        return pkt;
    }
    cout<<"packet found"<<endl;
    return pkt;
}
vector<Packet> User::query_packet_by_sender(string sender) {
    vector<Packet> packets = packet_db.get_by_sender(sender);
    if(packets.empty()){
        cout<<"No packet found with sender: "<<sender<<endl;
        return packets;
    }
    if(sender != account.username){
        auto new_end = remove_if(packets.begin(), packets.end(), [this](Packet pkt){
            return pkt.receiver != account.username;
        });
        packets.erase(new_end, packets.end());
    }   
    return packets;
}
vector<Packet> User::query_packet_by_receiver(string receiver) {
    vector<Packet> packets = packet_db.get_by_receiver(receiver);
    if(packets.empty()){
        cout<<"No packet found with receiver: "<<receiver<<endl;
        return packets;
    }
    if(receiver != account.username){
        auto new_end = remove_if(packets.begin(), packets.end(), [this](Packet pkt){
            return pkt.sender != account.username;
        });
        packets.erase(new_end, packets.end());
    }   
    return packets;
}
bool User::receive_packet(int tracking_number) {
    Packet pkt = packet_db.get_by_id(tracking_number);
    if(pkt.receiver != account.name){
        cout<<"error:packet not sent to you"<<endl;
        return false;
    }
    if(pkt.status == RECEIVED){
        cout<<"error:packet already received"<<endl;
        return false;
    }
    Packet new_pkt = pkt;
    new_pkt.status = RECEIVED;
    new_pkt.receive_time = get_time();
    packet_db.update(new_pkt);
    return true;
}
void User::change_password(string new_password) {
    account.password = new_password;
}
void User::recharge(int amount) {
    account.balance += amount;
    account_db.update(account);
}
bool User::send_packet(Packet pkt) {
    pkt.sender = account.username;
    account.balance -= 5;
    account_db.update(account);
    return packet_db.add(pkt);
}   
string User::get_name(){
    return account.name;
}

