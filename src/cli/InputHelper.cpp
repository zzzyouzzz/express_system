#include "InputHelper.h"

AccountInfo::AccountType InputHelper::get_account_type(){
    string temp;
    cin>>temp;
    if (temp == "user") {
        return AccountInfo::user;
    }
    else if (temp == "courier") {
        return AccountInfo::courier;
    }
    else if (temp == "admin") {
        return AccountInfo::admin;
    }
    else{
        cout<<"Invalid account type"<<endl;
        return AccountInfo::user;
    }
}

string InputHelper::get_account_id(){
    string temp;
    cin>>temp;
    if (temp == "-") {
        return "";
    }
    return temp;
}

string InputHelper::get_password(){
    string temp;
    cin>>temp;
    return temp;
}

int InputHelper::get_tracking_number(){
    int temp;
    if (cin>>temp) {
        temp = abs(temp);
    } else {
        temp = 0;
    }
    return temp;
}

string InputHelper::get_item_name(){
    string temp;
    cin>>temp;
    return temp;
}

Item::ItemType InputHelper::get_item_type(){
    string temp;
    cin>>temp;
    if (temp == "common") {
        return Item::commonItem;
    }
    else if (temp == "fragile") {
        return Item::fragileItem;
    }
    else if (temp == "book") {
        return Item::bookItem;
    }
    else{
        cout<<"Invalid item type"<<endl;
        return Item::commonItem;
    }
}

unsigned int InputHelper::get_amount(){
    unsigned int temp;
    cin>>temp;
    return temp;
}

string InputHelper::get_query_type(){
    string temp;
    cin>>temp;
    return temp;
}

service InputHelper::get_service(AccountInfo::AccountType account_type){
    if (account_type == AccountInfo::user) {
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                return send_packet;
            case 2:
                return query_packet;
            case 3:
                return change_password;
            case 4:
                return recharge;
            case 5:
                return receive_packet;
            case 6:
                return query_balance;
            case 7:
                return logout;
            default:
                cout<<"Invalid service"<<endl;
                return error;
        }
    } 
    else if (account_type == AccountInfo::courier) {
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                return collect_packet;
            case 2:
                return query_packet;
            case 3:
                return query_balance;
            case 4:
                return logout;
            default:
                cout<<"Invalid service"<<endl;
                return send_packet;
        }
    }
    else if (account_type == AccountInfo::admin) {
        int choice;
        cin>>choice;
        switch (choice) {
            case 1:
                return assign_courier;
            case 2:
                return query_packet;
            case 3:
                return logout;
            default:
                cout<<"Invalid service"<<endl;
                return send_packet;
        }
    }
    else {
        cout<<"Invalid account type"<<endl;
        return error;
    }
}

string InputHelper::get_time_info(){
    string temp;
    cin>>temp;
    if (temp == "-") {
        return "";
    }
    return temp;
}

string InputHelper::get_name(){
    string temp;
    cin>>temp;
    return temp;
}

string InputHelper::get_address(){
    string temp;
    cin>>temp;
    return temp;
}

string InputHelper::get_phone(){
    string temp;
    cin>>temp;
    return temp;
}