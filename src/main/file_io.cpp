#include "../include/express.h"
using namespace std;
void sys_init() {
    ifstream infile("../doc/accountdata.txt");
    if (infile.is_open()) {
        infile>>all_accounts_count;
        if(all_accounts_count>0){
            accounts.resize(all_accounts_count);
            for(int i=0;i<all_accounts_count;i++){
                int type;
                infile>>accounts[i].name>>accounts[i].phone>>accounts[i].password>>accounts[i].balance>>accounts[i].address>>type;
                accounts[i].type=static_cast<AccountType>(type);
            }
        } 
        infile.close();
    }
    else {
        cout << "Error:Failed to open file" << endl;
    }
    ifstream infile2("../doc/packetdata.txt");
    if (infile2.is_open()) {
        infile2>>all_packets_count;
        if(all_packets_count>0){
            packets.resize(all_packets_count);
            for(int i=0;i<all_packets_count;i++){
                int staus;
                infile2>>packets[i].id>>packets[i].sender>>packets[i].receiver>>packets[i].send_time>>packets[i].receive_time>>packets[i].content>>staus;
                packets[i].status=static_cast<PacketStatus>(staus);
            }
        } 
        infile2.close();
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
    outfile << all_accounts_count << endl;
    for (int i = 0;i < all_accounts_count;i++) {
        outfile << accounts[i].name << endl << accounts[i].phone << endl << accounts[i].password << endl << accounts[i].balance << endl << accounts[i].address << endl << static_cast<int>(accounts[i].type);
    }
    outfile.close();
    ofstream outfile2("../doc/packetdata.txt", ios::out);
    if (!outfile2.is_open()) {
        cout << "Error:Failed to open file" << endl;
        return 1;
    }
    outfile2 << all_packets_count << endl;
    for (int i = 0;i < all_packets_count;i++) {
        outfile2 << packets[i].id << endl << packets[i].sender << endl << packets[i].receiver << endl << packets[i].send_time << endl << packets[i].receive_time << endl << packets[i].content << endl << static_cast<int>(packets[i].status);
    }
    outfile2.close();
    return 0;
}
