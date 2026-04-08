#include "express.h"
using namespace std;
class Admin {
    private:
        Account &account;
        PacketDatabase &packet_db;
    public:
        Admin(Account &account, PacketDatabase &packet_db) :account(account), packet_db(packet_db) {}
        ~Admin() {}
        vector<Packet> query_packet_by_sender(string sender);
        vector<Packet> query_packet_by_receiver(string receiver);
        string get_name();
};
void adminloop(Admin admin);