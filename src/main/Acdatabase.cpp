#include "database.h"
AccountDatabase::AccountDatabase(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << filename << endl;
        return;
    }
    int count;
    file >> count;
    for (int i = 0; i < count; i++) {
        Account account;
        int type;
        file >> account.username >> account.password >> account.name >> account.phone >> account.address >> account.balance >> type;
        account.type = (AccountType)type;
        accounts[account.username] = account;
    }
    file.close();
    save_filename = filename;
}
bool AccountDatabase::add(Account account) {
    if(accounts.count(account.username) > 0) return false;
    accounts[account.username] = account;
    return true;
}
bool AccountDatabase::update(Account account) {
    if(accounts.count(account.username) == 0) return false;
    accounts[account.username] = account; 
    return true;
}
bool AccountDatabase::remove(string username) {
    if(accounts.count(username) == 0) return false;
    Account account = accounts[username];
    accounts.erase(username);
    return true;
}
Account AccountDatabase::get_by_username(string username) {
    if(accounts.count(username) == 0) return Account();
    return accounts[username];
}
AccountDatabase::~AccountDatabase() {
    ofstream file(save_filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << save_filename << endl;
        return;
    }
    file << accounts.size() << endl;
    for (auto& account : accounts) {
        file << account.second.username << " " << account.second.password << " " << account.second.name << " " << account.second.phone << " " << account.second.address << " " << account.second.balance << " " << (int)account.second.type << endl;
    }
    file.close();
}

/**/
