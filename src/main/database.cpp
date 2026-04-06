
    
/*#include "database.h"
AccountDatabase::AccountDatabase(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Failed to open file " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        Account account;
        
        accounts[account.id] = account;
        idx_username[account.username] = account.id;
    }
}*/