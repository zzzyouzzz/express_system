#include "admin.h"
using namespace std;
void Admin::query_packet(int type,string value){
    switch(type){
        case 0:
            for(auto pkt : packets) {
                cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
            }
            break;
        case 1:
            for(auto pkt : packets) {
                if(pkt.sender == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 2:
            for(auto pkt : packets) {
                if(pkt.receiver == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 3:
            for(auto pkt : packets) {
                if(pkt.send_time == value) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
            break;
        case 4:
            for(auto pkt : packets) {
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
                if(pkt.tracking_number == tn) {
                    cout<<"packet tracking number: "<<pkt.tracking_number<<" "<<"sender: "<<pkt.sender<<" "<<"receiver: "<<pkt.receiver<<" ";
                    cout<<"content: "<<pkt.content<<" "<<"sent time: "<<pkt.send_time<<" ";
                    cout<<"received time: "<<pkt.receive_time<<" "<<"status: "<<pkt.status<<endl;
                }
            }
        }          
        default:
            cout<<"Invalid query type!"<<endl;
            break;
    }
}
void Admin::query_user(){
    for(auto user : accounts) {
        cout<<"username: "<<user.username<<" "<<"name: "<<user.name<<" "<<"phone: "<<user.phone<<" "<<"address: "<<user.address<<" "<<"balance: "<<user.balance<<endl;
    }
}
string Admin::name(){
    return account.name;
}