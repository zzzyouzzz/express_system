#include "cli/ConsoleUI.h"
#include "dao/dao.h"
#include <fstream>
int main() {
    Database<int, Packet> packet_db;
    Database<string, AccountInfo> account_db;

    ifstream config_file("config.txt");
    if(!config_file.is_open()){
        cout<<"Error: Failed to open config file"<<endl;
        return 1;
    }
    string packet_filename;
    string account_filename;
    config_file>>account_filename>>packet_filename;
    config_file.close();

    cout<<"Loading databases..."<<endl;
    load_database(packet_filename, packet_db);
    load_database(account_filename, account_db);
    cout<<"Databases loaded successfully"<<endl;

    ConsoleUI ui=ConsoleUI(account_db);
    ui.run(packet_db, account_db);

    cout<<"Exiting program..."<<endl;
    save_database(packet_filename, packet_db);
    save_database(account_filename, account_db);
    return 0;
}