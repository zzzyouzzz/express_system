#include "ConsoleUI.h"
using namespace std;

AccountInfo ConsoleUI::main_menu(bool &is_signup) {
    AccountInfo account;
    cout<<"Welcome to the Express Delivery System!"<<endl;
    cout<<"Please enter your username:"<<endl;  
    account.username = InputHelper::get_account_id();
    cout<<"Please enter your password:"<<endl;
    account.password = InputHelper::get_password();
    AccountService::Error error;
    do {
        error = account_service.signin(account.username, account.password);
        switch (error) {
            case AccountService::ACCOUNT_NOT_FOUND:
                cout<<"Account not found"<<endl;
                cout<<"Please enter your username again or signup first(y/n):"<<endl;
                account.username = InputHelper::get_account_id();
                if (account.username == "y") {
                    is_signup = true;
                    cout<<"enter your username:"<<endl;
                    account.username = InputHelper::get_account_id();
                    cout<<"Please enter your password:"<<endl;
                    account.password = InputHelper::get_password();
                    cout<<"Please choose your account type(user/courier):"<<endl;
                    AccountInfo::AccountType type = InputHelper::get_account_type();
                    do {
                        error = account_service.signup(account.username, account.password, type);
                        switch (error) {
                            case AccountService::ACCOUNT_EXISTS:
                                cout<<"Account exists"<<endl;
                                cout<<"Please enter your username and password again to signup:"<<endl;
                                account.username = InputHelper::get_account_id();
                                account.password = InputHelper::get_password();
                                break;
                            case AccountService::ACCOUNT_TYPE_ERROR:
                                cout<<"Account type error"<<endl;
                                cout<<"Please choose your account type(user/courier):"<<endl;
                                type = InputHelper::get_account_type();
                                break;
                            case AccountService::SUCCESS:
                                cout<<"Signup success"<<endl;
                                cout<<"Login automatically"<<endl;
                                break;
                        }
                    } while (error != AccountService::SUCCESS);
                } else if(account.username == "n"){
                    cout<<"Signup failed"<<endl;
                    return AccountInfo();
                } else {
                    cout<<"Enter your password again:"<<endl;
                    account.password = InputHelper::get_password();
                }
                break;
            case AccountService::PASSWORD_ERROR:
                cout<<"Password error"<<endl;
                cout<<"Please enter your password again:"<<endl;
                account.password = InputHelper::get_password();
                break;
            case AccountService::SUCCESS:
                cout<<"Login success"<<endl;
                break;
        } 
    } while (error != AccountService::SUCCESS);
    return account;
}

void ConsoleUI::user_menu() {
    cout<<"User menu"<<endl;
    cout<<"1. Send packet"<<endl;
    cout<<"2. Query packet"<<endl;
    cout<<"3. Change password"<<endl;
    cout<<"4. Recharge"<<endl;
    cout<<"5. Receive packet"<<endl;
    cout<<"6. query balance"<<endl;
    cout<<"7. Logout"<<endl;
}

void ConsoleUI::courier_menu() {
    cout<<"Courier menu"<<endl;
    cout<<"1. Collect packet"<<endl;
    cout<<"2. Query packet"<<endl;
    cout<<"3. query balance"<<endl;
    cout<<"4. Logout"<<endl;
}

void ConsoleUI::admin_menu() {
    cout<<"Admin menu"<<endl;
    cout<<"1. Assign courier"<<endl;
    cout<<"2. Query packet"<<endl;
    cout<<"3. Logout"<<endl;
}

void ConsoleUI::run(Database<int, Packet> &packet_db, Database<string, AccountInfo> &account_db) {
    bool is_signup = false;
    AccountInfo account = main_menu(is_signup);
    if (account.empty()) {
        return;
    }
    account = account_db.find(account.username);
    if(is_signup) {
        cout<<"Hello, "<<account.username<<endl;
        cout<<"Please complete your account information:"<<endl;
        cout<<"Name:"<<endl;
        account.name = InputHelper::get_name();
        cout<<"Address:"<<endl;
        account.address = InputHelper::get_address();
        cout<<"Phone:"<<endl;
        account.phone = InputHelper::get_phone();
        account_service.completeAccount(account.username, account);
    }  
    cout<<"Hello, "<<account.username<<endl;
    Account *user;
    switch (account.type) {
        case AccountInfo::user:
            user = new User(packet_db, account_db);
            user_menu();
            break;
        case AccountInfo::courier:
            user = new Courier(packet_db, account_db);
            courier_menu();
            break;
        case AccountInfo::admin:
            user = new Admin(packet_db, account_db);
            admin_menu();
            break;
        default:
            cout<<"Invalid account type"<<endl;
            return;
    }
    service choice;
    do {
        cout<<"Please choose your service:"<<endl;
        choice = InputHelper::get_service(account.type);
        switch (choice) {
            case send_packet:{
                cout<<"Send packet"<<endl;
                cout<<"The receiver is:";
                string receiver = InputHelper::get_account_id();
                cout<<"The item type is:";
                Item::ItemType item_type = InputHelper::get_item_type();
                cout<<"The item is:";
                string item = InputHelper::get_item_name();
                user->send_packet(account.username, receiver, item_type, item);
                cout<<"Send packet success"<<endl;
                break;
            }
            case receive_packet:{
                cout<<"Receive packet"<<endl;
                Packet query_packet;
                query_packet.receiver = account.username;
                query_packet.status = Packet::PacketStatus::delivered;
                vector<Packet> packets = user->query_packet(account.username, query_packet);
                if(packets.empty()) {
                    cout<<"No packets to receive"<<endl;
                    break;
                }
                cout<<"Your packets to receive are as follows:"<<endl;
                for (Packet packet : packets) {
                    if (packet.status == Packet::PacketStatus::delivered) {
                        cout<<"tracking number: "<<packet.tracking_num<<endl;
                        cout<<"sender: "<<packet.sender<<"  "<<packet.goods->get_name()<<endl;
                        cout<<endl;
                    }
                }
                cout<<"Please choose the packet to receive by tracking number:"<<endl;
                int tracking_num;
                tracking_num = InputHelper::get_tracking_number();
                while (tracking_num != 0) { 
                    user->receive_packet(account.username, tracking_num);                  
                    cout<<"Receive packet "<<tracking_num<<" success"<<endl;
                    tracking_num = InputHelper::get_tracking_number();
                }              
                break;
            }
            case change_password:{
                cout<<"Change password"<<endl;
                cout<<"The new password is:";
                string new_password = InputHelper::get_password();
                user->change_password(account.username, new_password);
                cout<<"Change password success"<<endl;
                break;
            }
            case recharge:{
                cout<<"Recharge"<<endl;
                cout<<"The amount is:";
                unsigned int amount = InputHelper::get_amount();
                user->recharge(account.username, amount);
                cout<<"Recharge success"<<endl;
                break;
            }
            case assign_courier:{
                Packet query_packet;
                query_packet.courier_id = "assign";
                query_packet.status = Packet::pending;
                vector<Packet> packets = user->query_packet(account.username, query_packet);
                if(packets.empty()) {
                    cout<<"No packets to assign courier"<<endl;
                    break;
                }
                cout<<"Your packets to assign courier are as follows:"<<endl;
                for (Packet packet : packets) {
                    cout<<"tracking number: "<<packet.tracking_num<<endl;
                    cout<<"sender: "<<packet.sender<<"  receiver: "<<packet.receiver<<"  item: "<<packet.goods->get_name()<<endl;
                    cout<<endl;
                }
                cout<<"select a packet to assign courier"<<endl;
                int tracking_num;
                tracking_num = InputHelper::get_tracking_number();
                cout<<"Assign courier"<<endl;
                cout<<"The courier is:";
                string courier = InputHelper::get_account_id();
                user->assign_courier(tracking_num, courier);
                cout<<"Assign courier success"<<endl;
                break;
            }
            case collect_packet:{
                Packet query_packet;
                query_packet.status = Packet::PacketStatus::pending;
                vector<Packet> packets = user->query_packet(account.username, query_packet);
                if(packets.empty()) {
                    cout<<"No packets to collect"<<endl;
                    break;
                }
                cout<<"Your packets to collect are as follows:"<<endl;
                for (Packet packet : packets) {
                    cout<<"tracking number: "<<packet.tracking_num<<endl;
                    cout<<"sender: "<<packet.sender<<"  receiver: "<<packet.receiver<<endl;
                    cout<<endl;
                }
                cout<<"select a packet to collect"<<endl;
                cout<<"The packet is:";
                int tracking_num = InputHelper::get_tracking_number();
                user->collect_packet(account.username, tracking_num);
                cout<<"Collect packet success"<<endl;
                break;
            }
            case query_packet:{
                cout<<"Query packet"<<endl;
                Packet query_packet;
                cout<<"Enter some info to query:"<<endl;
                cout<<"\nThe sneder is: (- for all)";
                query_packet.sender = InputHelper::get_account_id();
                cout<<"\nThe receiver is: (- for all)";
                query_packet.receiver = InputHelper::get_account_id();
                cout<<"\nThe query send time is: (- for all)";
                query_packet.send_time = InputHelper::get_time_info();
                cout<<"\nThe query receive time is: (- for all)";
                query_packet.receive_time = InputHelper::get_time_info();
                vector<Packet> packets = user->query_packet(account.username, query_packet);
                if(packets.empty()) {
                    cout<<"No packets to query"<<endl;
                    break;
                }
                cout<<"Your packets are as follows:"<<endl;
                for (Packet packet : packets) {
                    cout<<"tracking number: "<<packet.tracking_num<<endl;
                    cout<<"sender: "<<packet.sender<<"  receiver: "<<packet.receiver<<"  item:  "<<packet.goods->get_name()<<endl;                
                    cout<<endl;
                }
                break;
            }
            case query_balance:{
                cout<<"Query balance"<<endl;
                cout<<"Your balance is:"<<user->get_balance(account.username)<<endl;
                break;
            }
            case logout:{
                cout<<"Logout"<<endl;
                break;
            }
            default:{
                cout<<"Invalid service"<<endl;
                while(cin);
                break;
            }
        }   
        
    } while (choice != logout);
}
