#include "../include/express.h"
#include "../include/User.h"
#include "../include/admin.h"

using namespace std;
int all_packets_count=0;
int all_accounts_count=0;
vector<Account> accounts;
vector<Packet> packets;
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
bool is_valid_username(string username) {//检查用户名是否有效
    for(auto user:accounts){
        if(user.username==username){
            return false;
        }
    }
    for (char c : username) {
        if (!isalnum(c) && c != '_') {
            return false;
        }
    }
    return true;
}
void signup() {
    Account new_user;
    new_user.type=USER;
    cout<<"Please input your username:"<<endl;
    cin>>new_user.username;
    while(!is_valid_username(new_user.username)){
        cout<<"Invalid username! Please input a valid username:"<<endl;
        cin>>new_user.username;
    }
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
    accounts.push_back(new_user);
    all_accounts_count++;
    cout<<"Signup success!"<<endl;
}
bool find_user(string username,Account& user){
    for (int i = 0;i < all_accounts_count;i++) {
        if (accounts[i].username == username) {
            user=accounts[i];
            return true;
        }
    }
    return false;
}
LoginStatus login(Account &user) {
    Account found_user;
    if(!find_user(user.username,found_user)){
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
                user.query_balance();
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
                user.query_packet(query_type,query_value);
                break;
            case 3:
                cout<<"your unreceived packets:"<<endl;
                user.query_packet(6,"");
                cout<<"Please input tracking number to receive:"<<endl;
                int tracking_number;
                cin>>tracking_number;
                user.receive_packet(tracking_number);
                break;
            case 4:
                user.send_packet();
                break;
            case 5:
                user.change_password();
                break;
            case 6:
                user.recharge();
                break;
            case 7:
                user.logout();
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
}
void adminloop(Admin admin){
    cout<<"Welcome "<<admin.name()<<"!"<<endl;
    cout<<"1.Query packet"<<endl;
    cout<<"2.Query user"<<endl;
    cout<<"3.Logout"<<endl;
    int choice=0;
    while(choice!=3){
        cout<<"Enter your choice:"<<endl;
        cin>>choice;
        switch(choice){
            case 1:
                admin.query_packet(0,"");
                break;
            case 2:
                admin.query_user();
                break;
            case 3:
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
}
int main() {
    AccountType now_user_type;
    sys_init();
    cout << "Hello!" << endl;
    string input;
    Account user;
    cout<<"Please input your username:"<<endl;
    cin>>user.username;
    while(input!="exit"){
        cout<<"Please input your password:"<<endl;
        cin>>user.password;
        switch(login(user)){
            case User_LOGIN_SUCCESS:
                cout<<"Login success!"<<endl;
                Userloop(User(user));
                input="exit";
                break;
            case Admin_LOGIN_SUCCESS:
                cout<<"Login success as admin!"<<endl;
                adminloop(Admin(0,user));
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
                    signup();
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
    save_data();
    return 0;
}