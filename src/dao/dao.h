#include "database.h"
#include <fstream>
#include <string>
#include <cstring>
#include <entity/Packet.h>
#include <entity/Item.h>
#include <entity/AccountInfo.h>
using namespace std;
/*template <typename Key, typename Data>
void load_database(string filename, Database<Key, Data> &db);

template <typename Key, typename Data>
bool save_database(string filename, Database<Key, Data> &db);*/

bool load_database(string filename, Database<int, Packet> &db);
bool save_database(string filename, Database<int, Packet> &db);
bool load_database(string filename, Database<string, AccountInfo> &db);
bool save_database(string filename, Database<string, AccountInfo> &db);