#include "User.h"
using namespace std;
void User::query_balance() {
    cout<<"balance: "<<account.balance<<endl;
}
void User::query_packet(int type=0,string value="") {
    switch(type){
        case 0:
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
            }
            break;
        case 1:
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                if(pkt.sender == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 2:
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                if(pkt.receiver == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 3:
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                if(pkt.send_time == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 4:
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                if(pkt.receive_time == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 5:{
            int tn=stoi(value);
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                if(pkt.tracking_number == tn) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
        }          
        case 6:
            for(auto pkt : packets) {
                if(pkt.sender != account.name && pkt.receiver != account.name) {
                    continue;
                }
                if(pkt.status == SENT&&pkt.receiver == account.name) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        default:
            cout<<"Invalid query type!"<<endl;
            break;
    }
}
void User::receive_packet(int tracking_number) {
    int i;
    for(i=0;i<all_packets_count;i++){
        if(packets[i].tracking_number == tracking_number){
            if(packets[i].status == RECEIVED){
                cout<<"error:packet already received"<<endl;
                break;
            }
            if(packets[i].receiver != account.name){
                cout<<"error:packet not sent to you"<<endl;
                break;
            }
            packets[i].status=RECEIVED;
            packets[i].receive_time=get_time();
            cout<<"receive packet success"<<endl;
            break;
        }
    }
    if(i==all_packets_count){
        cout<<"error:packet not found"<<endl;
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
    new_pkt.tracking_number =all_packets_count;
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
