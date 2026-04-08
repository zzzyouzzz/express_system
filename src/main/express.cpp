#include "express.h"
#include "User.h"
#include "admin.h"
#include "database.h"

using namespace std;
const string config_filename="config.txt";
int starttime;
int packet_count=0;
vector<int> read_packets() {//读取用户输入的包裹号
    vector<int> selected_packets;
    string input;
    int num=0;
    while(getchar()!='\n');//读取换行符
    getline(cin, input);
    int i=0;
    while(i<input.size()){//遍历输入字符串
        while(input[i]==' ')i++;
        while(input[i]>='0'&&input[i]<='9'){
            num=num*10+(input[i]-'0');
            i++;
        }
        selected_packets.push_back(num);
        num=0;
        while(input[i]!=' ')i++;
    }
    return selected_packets;
}
string get_time() {//获取当前时间
    time_t now = time(0);
    struct tm* t = localtime(&now);
    return to_string(t->tm_year + 1900) + "-" + to_string(t->tm_mon + 1) + "-" + to_string(t->tm_mday) + "_" + to_string(t->tm_hour) + ":" + to_string(t->tm_min) + ":" + to_string(t->tm_sec);
}
void signup(AccountDatabase &account_db) {
    Account new_user;
    new_user.type=USER;
    cout<<"Please input your username:"<<endl;
    cin>>new_user.username;
    cout<<"Please input your password:"<<endl;
    cin>>new_user.password;
    cout << "Please Compleate your information:" << endl;
    cout<<"Please input your name:"<<endl;
    cin>>new_user.name;
    cout<<"Please input your phone:"<<endl;
    cin>>new_user.phone;
    cout<<"Please input your address:"<<endl;
    cin>>new_user.address;
    new_user.balance=0;
    if(account_db.add(new_user)){
        cout<<"Signup success!"<<endl;
    }
    else{
        cout<<"Signup failed!"<<endl;
    }
}
LoginStatus login(Account &user,AccountDatabase &account_db) {
    Account found_user=account_db.get_by_username(user.username);
    if(found_user.username.empty()){
        return NOT_FOUND;
    }
    if(found_user.password==user.password&&found_user.type==USER){
        user=found_user;
        return User_LOGIN_SUCCESS;
    }
    else if(found_user.password==user.password&&found_user.type==ADMIN){
        user=found_user;
        return Admin_LOGIN_SUCCESS;
    }
    else{
        return FAIL;
    }
}
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
        int query_type=0;
        string query_value;
        switch(choice){
            case 1:
                cout<<"Your balance is:"<<user.get_balance()<<endl;
                break;
            case 2:
                cout<<"Please input query type:"<<endl;
                cout<<"1.Query by sender"<<endl;
                cout<<"2.Query by receiver"<<endl;
                cout<<"3.Query by send_time"<<endl;
                cout<<"4.Query by receive_time"<<endl;
                cout<<"5.Query by tracking number"<<endl;
                cout<<"0.Query all packets"<<endl;
                cin>>query_type>>query_value;
                switch(query_type){
                    case 1:
                        {cout<<"Your packets by sender:"<<query_value<<endl;
                        vector<Packet> packets=user.query_packet_by_sender(query_value);
                        if(packets.empty()){
                            cout<<"No packet found!"<<endl;
                        }
                        else{
                            for(Packet packet:packets){
                                cout<<"Packet found:"<<endl;
                                cout<<"Tracking number:"<<packet.tracking_number<<endl;
                                cout<<"Sender:"<<packet.sender<<endl;
                                cout<<"Receiver:"<<packet.receiver<<endl;
                                cout<<"Send time:"<<packet.send_time<<endl;
                                cout<<"Receive time:"<<packet.receive_time<<endl;
                                cout<<"Status:"<<packet.status<<endl;
                                cout<<"Content:"<<packet.content<<endl;
                            }
                        }
                        break;}
                    case 2:
                        {cout<<"Your packets by receiver:"<<query_value<<endl;
                        vector<Packet> packets=user.query_packet_by_receiver(query_value);
                        if(packets.empty()){
                            cout<<"No packet found!"<<endl;
                        }
                        else{
                            for(Packet packet:packets){
                                cout<<"Packet found:"<<endl;
                                cout<<"Tracking number:"<<packet.tracking_number<<endl;
                                cout<<"Sender:"<<packet.sender<<endl;
                                cout<<"Receiver:"<<packet.receiver<<endl;
                                cout<<"Send time:"<<packet.send_time<<endl;
                                cout<<"Receive time:"<<packet.receive_time<<endl;
                                cout<<"Status:"<<packet.status<<endl;
                                cout<<"Content:"<<packet.content<<endl;
                            }
                        }
                        break;}
                    default:
                        cout<<"Invalid query type!"<<endl;
                        break;
                }
                break;
            case 4:
                {Packet pkt;
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
            case 6:
                {cout<<"Please input your recharge amount:"<<endl;
                int amount;
                cin>>amount;
                user.recharge(amount);
                cout<<"Recharge success!"<<endl;
                break;
            case 7:
                cout<<"Logout success!"<<endl;
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;}
        }
    }
}
void adminloop(Admin admin){
    cout<<"Welcome "<<admin.get_name()<<"!"<<endl;
    cout<<"1.Query packet by sender"<<endl;
    cout<<"2.Query packet by receiver"<<endl;
    cout<<"3.Logout"<<endl;
    int choice=0;
    while(choice!=3){
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
                    for(Packet packet:packets){
                        cout<<"Packet found:"<<endl;
                        cout<<"Tracking number:"<<packet.tracking_number<<endl;
                        cout<<"Sender:"<<packet.sender<<endl;
                        cout<<"Receiver:"<<packet.receiver<<endl;
                        cout<<"Send time:"<<packet.send_time<<endl;
                        cout<<"Receive time:"<<packet.receive_time<<endl;
                        cout<<"Status:"<<packet.status<<endl;
                        cout<<"Content:"<<packet.content<<endl;
                    }
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
                    for(Packet packet:packets){
                        cout<<"Packet found:"<<endl;
                        cout<<"Tracking number:"<<packet.tracking_number<<endl;
                        cout<<"Sender:"<<packet.sender<<endl;
                        cout<<"Receiver:"<<packet.receiver<<endl;
                        cout<<"Send time:"<<packet.send_time<<endl;
                        cout<<"Receive time:"<<packet.receive_time<<endl;
                        cout<<"Status:"<<packet.status<<endl;
                        cout<<"Content:"<<packet.content<<endl;
                    }
                }
                break;}
            case 3:
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
}
int main() {
    string data_filename,packet_filename;
    ifstream config_file(config_filename);
    if(!config_file.is_open()){
        cout<<"Error: Failed to open file "<<config_filename<<endl;
        return 1;
    }
    config_file>>data_filename>>packet_filename;
    config_file.close();
    starttime=time(0);
    AccountDatabase account_db(data_filename);
    PacketDatabase packet_db(packet_filename);
    cout << "Hello!" << endl;
    string input;
    Account user;
    cout<<"Please input your username:"<<endl;
    cin>>user.username;
    while(input!="exit"){
        cout<<"Please input your password:"<<endl;
        cin>>user.password;
        switch(login(user,account_db)){
            case User_LOGIN_SUCCESS:
                cout<<"Login success!"<<endl;
                Userloop(User(user,packet_db,account_db));
                input="exit";
                break;
            case FAIL:
                cout<<"Login failed!"<<endl;
                break;
            case NOT_FOUND:
                cout<<"User not found!"<<endl;
                cout<<"Please input your name again or input signup to register."<<endl;
                cout<<"enter exit to logout."<<endl;
                cin>>input;
                if(input=="signup"){
                    signup(account_db);
                    cout<<"Please input your username to login again."<<endl;
                    cin>>user.username;
                }
                else if(input=="exit")continue;
                else{
                    user.username=input;
                }
                break;
        }
    }
    return 0;
}