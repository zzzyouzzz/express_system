#include "express.h"
#include "log.h"
#include "database.h"
#include "admin.h"
#include "User.h"
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
void print_Packet(vector<Packet> packets) {//打印包裹信息
    for(Packet packet:packets){
        cout<<"Packet "<<packet.tracking_number<<" found:"<<endl;
        cout<<"Sender:"<<packet.sender<<endl;
        cout<<"Receiver:"<<packet.receiver<<endl;
        cout<<"Send time:"<<packet.send_time<<endl;
        cout<<"Receive time:"<<packet.receive_time<<endl;
        cout<<"Status:"<<packet.status<<endl;
        cout<<"Content:"<<packet.content<<endl;
    }
}
void print_Account(Account account) {//打印账户信息
    cout<<"Username:"<<account.username<<endl;
    cout<<"Name:"<<account.name<<endl;
    cout<<"Phone:"<<account.phone<<endl;
    cout<<"Address:"<<account.address<<endl;
    cout<<"Balance:"<<account.balance<<endl;
    cout<<"Type:"<<account.type<<endl;
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
            case Admin_LOGIN_SUCCESS:
                cout<<"Login success!"<<endl;
                Adminloop(Admin(user,packet_db,account_db));
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