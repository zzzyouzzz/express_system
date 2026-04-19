#include "AccountService.h"

bool AccountService::transfer(string userID, string toUserID, unsigned int amount) {
    AccountInfo user = account_db.find(userID);
    AccountInfo toUser = account_db.find(toUserID);
    if (user.balance < amount) return false;
    user.balance -= amount;
    toUser.balance += amount;
    if (!account_db.update("balance", user, userID)) return false;
    if (!account_db.update("balance", toUser, toUserID)) return false;
    return true;
}

bool AccountService::deductionForSendExpress(string account_id, unsigned int express_price) {
    AccountInfo account = account_db.find(account_id);
    if (account.balance < express_price) return false;
    if (account.type != AccountInfo::AccountType::user) return false;
    if (!transfer(account_id, admin_id, express_price)) return false;
    return true;
}

bool AccountService::settleToCourier(string account_id, unsigned int express_price) {
    AccountInfo account = account_db.find(account_id);
    if (account.type != AccountInfo::AccountType::courier) return false;
    if (!transfer(admin_id, account_id, express_price)) return false;
    return true;
}

bool AccountService::recharge(string account_id, unsigned int amount) {
    AccountInfo account = account_db.find(account_id);
    if (account.type != AccountInfo::AccountType::user) return false;
    account.balance += amount;
    if (!account_db.update("balance", account, account_id)) return false;
    return true;
}

AccountService::Error AccountService::signin(string account_id, string password) {
    AccountInfo account = account_db.find(account_id);
    if (account.empty()) return ACCOUNT_NOT_FOUND;
    if (account.password != password) return PASSWORD_ERROR;
    return SUCCESS;
}

AccountService::Error AccountService::signup(string account_id, string password, AccountInfo::AccountType type) {
    AccountInfo account = account_db.find(account_id);
    if (!account.empty()) return ACCOUNT_EXISTS;
    if (type == AccountInfo::AccountType::admin) return ACCOUNT_TYPE_ERROR;
    account.username = account_id;
    account.name = "new_user";
    account.type = type;
    account.password = password;
    account.balance = 0;
    account_db.insert(account, account_id);
    return SUCCESS;
}

bool AccountService::completeAccount(string account_id, AccountInfo account_info) {
    AccountInfo account = account_db.find(account_id);
    if (account.empty()) return false;
    account = account_info;
    try {
        if (!account_db.update("name", account, account_id)) throw runtime_error("Failed to update name");
        if (!account_db.update("address", account, account_id)) throw runtime_error("Failed to update address");
        if (!account_db.update("phone", account, account_id)) throw runtime_error("Failed to update phone");
        account_db.commit();
        return true;
    } catch (const runtime_error &e) {
        account_db.rollback();
        return false;
    }
}