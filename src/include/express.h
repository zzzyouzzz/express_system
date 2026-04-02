#ifndef EXPRESS_H
#define EXPRESS_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
const int MAX_USER = 100;
enum LoginStatus {
    User_LOGIN_SUCCESS,
    Admin_LOGIN_SUCCESS,
    FAIL,
    NOT_FOUND
};
enum AccountType {
    USER,
    ADMIN
};
enum PacketStatus {
    SENT,
    RECEIVED
};
struct Account {
    string username;
    string name;
    string phone;
    string password;
    int balance;
    string address;
    AccountType type;
    Account() :type(USER) {}
    Account(string username, string name, string phone, string password, int balance, string address) :username(username), name(name), phone(phone), password(password), balance(balance), address(address), type(USER) {}
};
struct Packet{
    int tracking_number;
    string sender;
    string receiver;
    string send_time;
    string receive_time;
    PacketStatus status;
    string content;
    Packet(){}
    Packet(string sender, string receiver, string send_time, string receive_time, string content) :status(SENT), sender(sender), receiver(receiver), send_time(send_time), receive_time(receive_time), content(content) {}
};
class IPacketQuery {
public:
    virtual ~IPacketQuery() = default;
    virtual void query_packet(int type=0,string value="") = 0;
};
extern vector<Account> accounts;
extern vector<Packet> packets;
extern int all_packets_count;
extern int all_accounts_count;

vector<int> read_packets();
string get_time();
void signup();
LoginStatus login(Account &user);
bool find_user(string name,Account& user);
void sys_init();
void save_data();
bool is_valid_username(string username);
#endif
