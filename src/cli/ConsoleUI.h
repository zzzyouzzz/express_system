#pragma once
#include "service/Account.h"
#include "service/AccountService.h"
#include "dao/Database.h"
#include "entity/AccountInfo.h"
#include <iostream>
#include "InputHelper.h"
#include "service/User.h"
#include "service/Courier.h"
#include "service/Admin.h"

class ConsoleUI {
    private:
        AccountService account_service;
    public:
        ConsoleUI(Database<string, AccountInfo> &account_db) : account_service(account_db) {}
        AccountInfo main_menu(bool &is_signup);
        void user_menu();
        void courier_menu();
        void admin_menu();
        void run(Database<int, Packet> &packet_db, Database<string, AccountInfo> &account_db);
};