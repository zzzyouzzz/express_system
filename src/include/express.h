#ifndef EXPRESS_H
#define EXPRESS_H
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

extern int starttime;
extern int packet_count;
vector<int> read_packets();
string get_time();
class User;
class Admin;
struct Packet;
struct Account;
void Userloop(User user);
void Adminloop(Admin admin);
void print_Packet(vector<Packet> packets);
void print_Account(Account account);
#endif
