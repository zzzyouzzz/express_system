#include "User.h"
#include "express.h"
void Userloop(User user){
    cout<<"Welcome "<<user.get_name()<<"!"<<endl;
    cout<<"1.Query balance"<<endl;
    cout<<"2.Query packet"<<endl;
    cout<<"3.receive packet"<<endl;
    cout<<"4.Send packet"<<endl;
    cout<<"5.Change password"<<endl;
    cout<<"6.Recharge"<<endl;
    cout<<"7.Logout"<<endl;
    int choice=0;
    while(choice!=7){
        cout<<"Enter your choice:"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Your balance is:"<<user.get_balance()<<endl;
                break;
            case 2:{
                cout<<"Please input query type:"<<endl;
                cout<<"1.Query by sender"<<endl;
                cout<<"2.Query by receiver"<<endl;
                cout<<"3.Query by send_time"<<endl;
                cout<<"4.Query by receive_time"<<endl;
                cout<<"5.Query by tracking number"<<endl;
                cout<<"0.Query all packets"<<endl;
                int query_type;
                string query_value;
                cin>>query_type>>query_value;
                switch(query_type){
                    case 1:
                        {cout<<"Your packets by sender:"<<query_value<<endl;
                        vector<Packet> packets=user.query_packet_by_sender(query_value);
                        if(packets.empty()){
                            cout<<"No packet found!"<<endl;
                        }
                        else{
                            print_Packet(packets);
                        }
                        break;}
                    case 2:
                        {cout<<"Your packets by receiver:"<<query_value<<endl;
                        vector<Packet> packets=user.query_packet_by_receiver(query_value);
                        if(packets.empty()){
                            cout<<"No packet found!"<<endl;
                        }
                        else{
                            print_Packet(packets);
                        }
                        break;}
                    case 3:
                        {cout<<"Your packets by send_time:"<<query_value<<endl;
                        vector<Packet> packets=user.query_packet_by_send_time(query_value);
                        if(packets.empty()){
                            cout<<"No packet found!"<<endl;
                        }
                        else{
                            print_Packet(packets);
                        }
                        break;}
                    case 4:
                        {cout<<"Your packets by receive_time:"<<query_value<<endl;
                        vector<Packet> packets=user.query_packet_by_receive_time(query_value);
                        if(packets.empty()){
                            cout<<"No packet found!"<<endl;
                        }
                        else{
                            print_Packet(packets);
                        }
                        break;}
                    default:
                        cout<<"Invalid query type!"<<endl;
                        break;
                }
                break;}
            case 3:{
                cout<<"Please input your tracking number:"<<endl;
                int tracking_number;
                cin>>tracking_number;
                if(user.receive_packet(tracking_number)){
                    cout<<"Receive packet success!"<<endl;
                }
                else{
                    cout<<"Receive packet failed!"<<endl;
                }
                break;
            }
            case 4:{
                if(user.get_balance()<5){
                    cout<<"Insufficient balance!"<<endl;
                    break;
                }
                Packet pkt;
                cout<<"Please input your recipient name:"<<endl;
                cin>>pkt.receiver;
                cout<<"Please input your packet content:"<<endl;
                cin>>pkt.content;
                pkt.status=PacketStatus::SENT;
                pkt.send_time=get_time();
                pkt.receive_time="----";
                pkt.tracking_number=starttime+packet_count;
                packet_count++;
                if(user.send_packet(pkt)){
                    cout<<"Send packet success!"<<endl;
                }
                else{
                    cout<<"Send packet failed!"<<endl;
                }
                break;}
            case 5:
                {cout<<"Please input your new password:"<<endl;
                string new_password;
                cin>>new_password;
                user.change_password(new_password);
                break;}
            case 6:{
                cout<<"Please input your recharge amount:"<<endl;
                int amount;
                cin>>amount;
                user.recharge(amount);
                cout<<"Recharge success!"<<endl;
                break;
                }
            case 7:
                cout<<"Logout success!"<<endl;
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
}