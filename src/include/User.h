#ifndef USER_H
#define USER_H
#include "express.h"
using namespace std;
class User:public IPacketQuery{
    private:
        int userId;
        Account account;
    public:
        User( Account account) : account(account) {}
        void query_balance();
        void query_packet(int type,string value) override;
        void receive_packet(int tracking_number);
        void send_packet();
        void change_password();
        void recharge();
        void logout();
        string get_name();
};
void Userloop(User user);
#endif
