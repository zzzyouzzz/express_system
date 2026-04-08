#include "admin.h"
using namespace std;
vector<Packet> Admin::query_packet_by_sender(string sender){
    vector<Packet> packets = packet_db.get_by_sender(sender);
    if(packets.empty()){
        cout<<"No packet found with sender: "<<sender<<endl;
        return {};  
    }
    return packets;
    
}
vector<Packet> Admin::query_packet_by_receiver(string receiver){
    vector<Packet> packets = packet_db.get_by_receiver(receiver);
    if(packets.empty()){
        cout<<"No packet found with receiver: "<<receiver<<endl;
        return {};  
    }
    return packets;
}
string Admin::get_name(){
    return account.name;
}