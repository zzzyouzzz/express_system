#pragma once
#include <string>
#include <iostream>
#include "entity/AccountInfo.h"
#include "entity/Item.h"
using namespace std;
enum service {
    send_packet,
    receive_packet,
    change_password,
    recharge,
    assign_courier,
    collect_packet,
    query_packet,
    query_balance,
    logout,
    error
};
class InputHelper{
    public:
        static AccountInfo::AccountType get_account_type();
        static string get_account_id();
        static string get_password();
        static int get_tracking_number();
        static string get_item_name();
        static Item::ItemType get_item_type();
        static unsigned int get_amount();
        static string get_query_type();
        static service get_service(AccountInfo::AccountType account_type);
        static string get_time_info();
        static string get_name();
        static string get_address();
        static string get_phone();
};
