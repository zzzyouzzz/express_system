#ifndef USER_H
#define USER_H
#include "express.h"
using namespace std;
class User{
    private:
        int userId;
        Account account;
    public:
        User( Account account) : account(account) {}
        void query_balance();
        void query_packet();
        int query_receive_packet();
        void receive_packet();
        void send_packet();
        void change_password();
        void recharge();
        string get_name();
};
string Userloop(User user);
#endif
