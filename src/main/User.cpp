#include "../include/User.h"
using namespace std;
void User::query_balance() {
    cout<<"balance: "<<account.balance<<endl;
}
void User::query_packet() {
    bool found = false;
    for(auto pkt : packets) {
        if(pkt.sender == account.name) {
            found = true;
            cout<<"sent time: "<<pkt.send_time<<" "<<"receiver: "<<pkt.receiver<<" "<<"status: "<<pkt.status<<" "<<"content: "<<pkt.content<<endl;
        }
        else if(pkt.receiver == account.name) {
            found = true;
            cout<<"received time: "<<pkt.receive_time<<" "<<"sender: "<<pkt.sender<<" "<<"status: "<<pkt.status<<" "<<"content: "<<pkt.content<<endl;
        }
    }
    if(!found) {
        cout<<"no sent or received packet"<<endl;
    }
}
int User::query_receive_packet() {
    int found = 0;
    for(auto pkt : packets) {
        if(pkt.receiver == account.name&&pkt.status == SENT) {
            found++;
            cout<<"packet id: "<<pkt.id<<" "<<"sent time: "<<pkt.send_time<<" "<<"receiver: "<<pkt.receiver<<" "<<"status: "<<pkt.status<<" "<<"content: "<<pkt.content<<endl;
        }
    }
    if(!found) {
        cout<<"no received packet"<<endl;
    }
    return found;
}
void User::receive_packet() {
    int packets_count=query_receive_packet();
    if(packets_count==0)return;
    int select_counts=0;
    while(select_counts<packets_count){
        cout<<"Please select one or more packet to receive(just input packet id,separate by space): "<<endl;
        vector<int> selected_packets=read_packets();
        for(int i=0;i<selected_packets.size();i++){
            int select_packet_id=selected_packets[i];
            bool found = false;
            for(int i=0;i<all_packets_count;i++) {
                if(packets[i].id == select_packet_id) {
                    select_counts++;
                    packets[i].status=RECEIVED;
                    found = true;
                    packets[i].receive_time=get_time();
                    cout<<packets[i].receive_time<<" "<<"receive packet from "<<packets[i].sender<<" success"<<endl;
                    break;
                }
            }
            if(!found) {
                cout<<"error:packet id "<<select_packet_id<<" not found"<<endl;
            }
        }
        if(select_counts<packets_count){
            cout<<"There are "<<packets_count-select_counts<<" more packet to receive"<<endl;
            cout<<"Please input \"continue\" to receive packet OR input \"exit\" to finish"<<endl;
            string input;
            cin>>input;
            if(input=="exit"){
                break;
            }
        }
    }
    if(select_counts==packets_count){
        cout<<"all packet received"<<endl;
    } 
}
void User::change_password() {
    cout<<"enter new password: ";
    cin>>account.password;
    cout<<"change password success"<<endl;
}
void User::recharge() {
    int amount;
    cout<<"enter recharge amount: ";
    cin>>amount;
    if(amount <= 0) {
        cout<<"recharge amount must be greater than 0"<<endl;
        return;
    }
    account.balance += amount;
    cout<<"recharge success"<<endl;
    query_balance();
}
void User::send_packet(){
    if(account.balance<5){
        cout<<"error:balance not enough"<<endl;
        return;
    }
    Packet new_pkt;
    new_pkt.sender=account.name;
    cout<<"enter receiver name: ";
    cin>>new_pkt.receiver;
    cout<<"enter content: ";
    cin>>new_pkt.content;
    new_pkt.id=all_packets_count;
    new_pkt.send_time=get_time();
    new_pkt.receive_time="----";
    new_pkt.status=SENT;
    packets.push_back(new_pkt);
    all_packets_count++;
    account.balance-=5;
    cout<<"send packet success"<<endl;
}   
string User::get_name(){
    return account.name;
}
void User::logout(){
    for(int i=0;i<all_accounts_count;i++){
        if(accounts[i].name == account.name){
            accounts[i]=account;
            break;
        }
    }
    cout<<"logout success"<<endl;
}
