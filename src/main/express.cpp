#include "../include/express.h"
using namespace std;
Account::Account() {
    this->type = USER;
}
Account::Account(int id, string name, string phone, string password, int balance, string address) {
    this->id = id;
    this->name = name;
    this->phone = phone;
    this->password = password;
    this->balance = balance;
    this->address = address;
    this->type = type;
}
Account signup() {
    string name, phone, password, address;
    cout << "Please input your name,phone,password,address:" << endl;
    cin >> name >> phone >> password >> address;
    return Account(user_count, name, phone, password, 0, address);
}
int find_user(string name) {
    for (int i = 0;i < user_count;i++) {
        if (accounts[i].name == name) {
            return i;
        }
    }
    return -1;
}
int login(AccountType& user_out) {
    string name, password;
    int id;
    cout << "Please input your name:" << endl;
    cin >> name;
    if ((id = find_user(name)) != -1) {
        cout << "Please input your password:" << endl;
        cin >> password;
        if (accounts[id].password == password) {
            user_out = accounts[id].type;
            return LoginStatus::SUCCESS;
        }
        else {
            return LoginStatus::FAIL;
        }
    }
    else {
        return LoginStatus::NOT_FOUND;
    }
}
/**/
void init() {
    ifstream infile("../doc/accountdata.txt");
    if (infile.is_open()) {
        while (!infile.eof()) {
            infile >> accounts[user_count].id >> accounts[user_count].name >> accounts[user_count].phone >> accounts[user_count].password >> accounts[user_count].balance >> accounts[user_count].address;
            user_count++;
        }
        user_count--;
        infile.close();
    }
    else {
        cout << "Error:Failed to open file" << endl;
    }
}
int logout() {
    ofstream outfile("../doc/accountdata.txt", ios::out);
    if (!outfile.is_open()) {
        cout << "Error:Failed to open file" << endl;
        return 1;
    }
    for (int i = 0;i < user_count;i++) {
        outfile << accounts[i].id << endl << accounts[i].name << endl << accounts[i].phone << endl << accounts[i].password << endl << accounts[i].balance << endl << accounts[i].address << endl;
    }
    outfile.close();
    return 0;
}
void User::Userloop() {
    cout << "input 1 to logout" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        logout();
    }

}
int main() {
    AccountType now_user_type;
    init();
    cout << "Hello!" << endl;
    switch (login(now_user_type)) {
    case SUCCESS:
        cout << "Login Success" << endl;
        if (now_user_type == AccountType::USER) {
            User user;
            user.Userloop();
        }
        else {
            cout << "Admin" << endl;
        }
        break;
    case FAIL:
        cout << "Login Fail" << endl;
        break;
    case NOT_FOUND:
        cout << "User Not Found,Please Signup First" << endl;
        accounts[user_count] = signup();
        user_count++;
        User user;
        user.Userloop();
        break;
    }
    return 0;
}