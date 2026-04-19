#include "dao.h"

bool load_database(string filename, Database<int, Packet> &db) {
    db.create_index("sender", [](Packet p) { return p.sender; });
    db.create_index("receiver", [](Packet p) { return p.receiver; });
    db.create_index("send_time", [](Packet p) { return p.send_time; });
    db.create_index("receive_time", [](Packet p) { return p.receive_time; });
    db.create_index("courier_id", [](Packet p) { return p.courier_id; });

    ifstream file(filename);
    if (!file.is_open()) return false;
    int num;
    file >> num;
    for (int i = 0; i < num; i++) {
        Packet info;
        int status;
        file >> info.tracking_num >> info.sender >> info.receiver >> info.send_time >> info.receive_time >> status;
        info.status = (Packet::PacketStatus)status;
        int item_type;
        string name;
        file >> item_type >> name;
        switch (item_type) {
            case Item::ItemType::commonItem:
                info.goods = new CommonItem(name);
                break;
            case Item::ItemType::fragileItem:
                info.goods = new FragileItem(name);
                break;
            case Item::ItemType::bookItem:
                info.goods = new BookItem(name);
                break;
            default:
                info.goods = nullptr;
        }
        file >> info.courier_id;
        db.insert(info, info.tracking_num);
    }
    file.close();
    return true;
}

bool save_database(string filename, Database<int, Packet> &db) {
    ofstream file(filename);
    if (!file.is_open()) return false;
    file << db.size() << endl;
    Iterator<Packet, int> it = db.iterator();
    while(it.has_next()){
        Packet info = it.next();
        file << info.tracking_num << endl;
        file << info.sender << endl;
        file << info.receiver << endl;
        file << info.send_time << endl;
        file << info.receive_time << endl;
        file << (int)info.status << endl;
        file << (int)info.goods->get_type() << endl;
        file << info.goods->get_name() << endl;
        file << info.courier_id << endl;
        delete info.goods;
    }
    file.close();
    return true;
}

bool load_database(string filename, Database<string, AccountInfo> &db) {
    
    ifstream file(filename);
    if (!file.is_open()) return false;
    int num;
    file >> num;
    for (int i = 0; i < num; i++) {
        AccountInfo info;
        int type;
        file >> info.username >> info.password >> info.name >> info.phone >> info.address >> info.balance >> type;
        info.type = (AccountInfo::AccountType)type;
        db.insert(info, info.username);
    }
    file.close();
    return true;
}

bool save_database(string filename, Database<string, AccountInfo> &db) {
    ofstream file(filename);
    if (!file.is_open()) return false;
    file << db.size() << endl;
    Iterator<AccountInfo, string> it = db.iterator();
    while(it.has_next()){
        AccountInfo info = it.next();
        file << info.username << endl;
        file << info.password << endl;
        file << info.name << endl;
        file << info.phone << endl;
        file << info.address << endl;
        file << info.balance << endl;
        file << (int)info.type << endl;
    }
    file.close();
    return true;
}