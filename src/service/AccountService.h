#pragma once
#include "dao/Database.h"
#include "entity/AccountInfo.h"
class AccountService {
    private:
        Database<string, AccountInfo> &account_db;
        string admin_id;
        bool transfer(string userID, string toUserID, unsigned int amount);
    public:
        enum Error {
            ACCOUNT_NOT_FOUND,
            PASSWORD_ERROR,
            ACCOUNT_EXISTS,
            ACCOUNT_TYPE_ERROR,
            SUCCESS
        };
        AccountService(Database<string, AccountInfo> &account_db) : account_db(account_db), admin_id("admin") {}
        bool deductionForSendExpress(string account_id, unsigned int express_price);
        bool settleToCourier(string account_id, unsigned int express_price);
        bool recharge(string account_id, unsigned int amount);
        Error signin(string account_id, string password);
        Error signup(string account_id, string password, AccountInfo::AccountType type);
        bool completeAccount(string account_id, AccountInfo account_info);
};