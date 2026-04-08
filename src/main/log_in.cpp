#include "log.h"
#include <iostream>
using namespace std;
void signup(AccountDatabase &account_db) {
    Account new_user;
    new_user.type=USER;
    cout<<"Please input your username:"<<endl;
    cin>>new_user.username;
    cout<<"Please input your password:"<<endl;
    cin>>new_user.password;
    cout << "Please Compleate your information:" << endl;
    cout<<"Please input your name:"<<endl;
    cin>>new_user.name;
    cout<<"Please input your phone:"<<endl;
    cin>>new_user.phone;
    cout<<"Please input your address:"<<endl;
    cin>>new_user.address;
    new_user.balance=0;
    if(account_db.add(new_user)){
        cout<<"Signup success!"<<endl;
    }
    else{
        cout<<"Signup failed!"<<endl;
    }
}
LoginStatus login(Account &user,AccountDatabase &account_db) {
    Account found_user=account_db.get_by_username(user.username);
    if(found_user.username.empty()){
        return NOT_FOUND;
    }
    if(found_user.password==user.password&&found_user.type==USER){
        user=found_user;
        return User_LOGIN_SUCCESS;
    }
    else if(found_user.password==user.password&&found_user.type==ADMIN){
        user=found_user;
        return Admin_LOGIN_SUCCESS;
    }
    else{
        return FAIL;
    }
}