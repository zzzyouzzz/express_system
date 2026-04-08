#include "express.h"
#include "admin.h"
void Adminloop(Admin admin){
    cout<<"Welcome "<<admin.get_name()<<"!"<<endl;
    cout<<"1.Query packet by sender"<<endl;
    cout<<"2.Query packet by receiver"<<endl;
    cout<<"3.Query account"<<endl;
    cout<<"4.Logout"<<endl;
    int choice=0;
    while(choice!=4){
        cout<<"Enter your choice:"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                {cout<<"Please input your sender name:"<<endl;
                string query_value;
                cin>>query_value;
                vector<Packet> packets=admin.query_packet_by_sender(query_value);
                if(packets.empty()){
                    cout<<"No packet found!"<<endl;
                }
                else{
                    print_Packet(packets);
                }
                break;}
            case 2:
                {cout<<"Please input your receiver name:"<<endl;
                string query_value;
                cin>>query_value;
                vector<Packet> packets=admin.query_packet_by_receiver(query_value);
                if(packets.empty()){
                    cout<<"No packet found!"<<endl;
                }
                else{
                    print_Packet(packets);
                }
                break;}
            case 3:
                {
                    cout<<"Please input your username:"<<endl;
                    string query_value;
                    cin>>query_value;
                    Account account=admin.query_account(query_value);
                    if(account.username.empty()){
                        cout<<"No account found with username: "<<query_value<<endl;
                    }
                    else{
                        print_Account(account);
                    }
                    break;
                }
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
}