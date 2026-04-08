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
        file >> account.id >> account.username >> account.password >> account.name >> account.phone >> account.address >> account.balance >> type;
        account.type = (AccountType)type;
        accounts[account.id] = account;
        idx_username[account.username] = account.id;
    }
    file.close();
    save_filename = filename;
}
bool AccountDatabase::add(Account account) {
    if(accounts.count(account.id) > 0) return false;
    accounts[account.id] = account;
    idx_username[account.username] = account.id;
    return true;
}
bool AccountDatabase::update(Account account) {
    if(accounts.count(account.id) == 0) return false;
    Account old_account = accounts[account.id];
    idx_username.erase(old_account.username);
    idx_username[account.username] = account.id;
    accounts[account.id] = account; 
    return true;
}
bool AccountDatabase::remove(int id) {
    if(accounts.count(id) == 0) return false;
    Account account = accounts[id];
    idx_username.erase(account.username);
    accounts.erase(id);
    return true;
}
Account* AccountDatabase::get_by_id(int id) {
    if(accounts.count(id) == 0) return nullptr;
    return &accounts[id];
}
Account* AccountDatabase::get_by_username(string username) {
    if(idx_username.count(username) == 0) return nullptr;
    return &accounts[idx_username[username]];
}
AccountDatabase::~AccountDatabase() {
    ofstream file(save_filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << save_filename << endl;
        return;
    }
    file << accounts.size() << endl;
    for (auto& account : accounts) {
        file << account.second.id << " " << account.second.username << " " << account.second.password << " " << account.second.name << " " << account.second.phone << " " << account.second.address << " " << account.second.balance << " " << (int)account.second.type << endl;
    }
    file.close();
}

/**/
