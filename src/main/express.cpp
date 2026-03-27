#include "../include/express.h"
#include "../include/User.h"

using namespace std;
int all_packets_count=0;
int all_accounts_count=0;
vector<Account> accounts;
vector<Packet> packets;
vector<int> read_packets() {
    vector<int> selected_packets;
    string input;
    int num=0;
    getline(cin, input);
    char ch=input[0];
    while(ch!='\n'){
        while(ch==' ')ch++;
        while(ch>='0'&&ch<='9'){
            num=num*10+(ch-'0');
            ch++;
        }
        selected_packets.push_back(num);
        num=0;
        while(ch!=' ')ch++;
    }
    return selected_packets;
}
string get_time() {
    time_t now = time(0);
    struct tm* t = localtime(&now);
    return to_string(t->tm_year + 1900) + "-" + to_string(t->tm_mon + 1) + "-" + to_string(t->tm_mday) + " " + to_string(t->tm_hour) + ":" + to_string(t->tm_min) + ":" + to_string(t->tm_sec);
}
void signup() {
    Account new_user;
    new_user.type=USER;
    cout << "Please input your name,phone,password,address:" << endl;
    cin >> new_user.name >> new_user.phone >> new_user.password >> new_user.address;
    accounts.push_back(new_user);
    all_accounts_count++;
    cout<<"Signup success!"<<endl;
}
bool find_user(string name,Account& user){
    for (int i = 0;i < all_accounts_count;i++) {
        if (accounts[i].name == name) {
            user=accounts[i];
            return true;
        }
    }
    return false;
}
LoginStatus login(Account &user) {
    Account found_user;
    if(!find_user(user.name,found_user)){
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
string Userloop(User user){
    cout<<"Welcome "<<user.get_name()<<"!"<<endl;
    cout<<"1.Query balance"<<endl;
    cout<<"2.Query packet"<<endl;
    cout<<"3.Query receive packet"<<endl;
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
                user.query_balance();
                break;
            case 2:
                user.query_packet();
                break;
            case 3:
                user.query_receive_packet();
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
                logout();
                break;
            default:
                cout<<"Invalid choice!"<<endl;
                break;
        }
    }
    return "exit";
}
int main() {
    AccountType now_user_type;
    sys_init();
    cout << "Hello!" << endl;
    string input;
    Account user;
    cout<<"Please input your name:"<<endl;
    cin>>user.name;
    while(input!="exit"){
        cout<<"Please input your password:"<<endl;
        cin>>user.password;
        switch(login(user)){
            case User_LOGIN_SUCCESS:
                cout<<"Login success!"<<endl;
                input=Userloop(User(user));
                cout<<"Logout success!"<<endl;
                break;
            case Admin_LOGIN_SUCCESS:
                cout<<"Login success as admin!"<<endl;
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
                    cout<<"Please input your name to login again."<<endl;
                    cin>>user.name;
                }
                else if(input=="exit")continue;
                else{
                    user.name=input;
                }
                break;
        }
    }
    return 0;
}