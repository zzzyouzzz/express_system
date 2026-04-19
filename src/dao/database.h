#ifndef DATABASE_H
#define DATABASE_H
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
enum FeildType {
    STRING,
    INTEGER,
    FLOAT,
    BOOLEAN,
};
struct Feild {
    string name;
    FeildType type;
    size_t offset;
    size_t size;
};
template <typename Data, typename Key>
struct UndoLog {
    string record_name;
    Key key;
    Data old_info;
};

template <typename Data, typename Key>
class Iterator {
    private:
        const map<Key, Data> &table;
        typename map<Key, Data>::const_iterator it;
    public:
        Iterator(const map<Key, Data> &table) : table(table), it(table.begin()) {};
        bool has_next();
        Data next();
};

template <typename Key, typename Data>
class Index {
    private:
        function<string(Data)> get_record;
    public:
        map<string, vector<Key>> idx_map;
        Index() {}
        Index(function<string(Data)> fun, map<Key, Data> table);       
        void insert(Data info, Key i);
        bool remove(Data info, Key i);
        vector<Key> find(string record);
};

template <typename Key, typename Data>
class Database {
    private:
        map<Key, Data> table;
        map<string, Index<Key, Data>> indices;
        vector<Feild> feilds;
        vector<UndoLog<Data, Key>> undo_logs;
        bool is_committed;
    public:
        Database() : is_committed(false) {}
        void create_index(string record_name, function<string(Data)> fun);
        void insert(Data info, Key key);
        void remove(Key key);
        Data find(Key key);
        vector<Data> find(string record_name, string record_value);
        vector<Data> findall();
        bool update(string record_name, Data new_info, Key key);
        int size();
        Iterator<Data, Key> iterator();
        void commit();
        void rollback();
};

template <typename Key, typename Data>
void Database<Key, Data>::create_index(string record_name, function<string(Data)> fun) {
    indices.emplace(record_name, Index<Key, Data>(fun, table));
}

template <typename Key, typename Data>
Index<Key, Data>::Index(function<string(Data)> fun, map<Key, Data> table) {
    get_record = fun;
    for (auto &item : table) {
        string record = get_record(item.second);
        idx_map[record].push_back(item.first);
    }
}

template <typename Key, typename Data>
void Index<Key, Data>::insert(Data info, Key i) {
    idx_map[get_record(info)].push_back(i);
}

template <typename Key, typename Data>
bool Index<Key, Data>::remove(Data info, Key i) {
    string record = get_record(info);
    if (idx_map.count(record) == 0) return false;
    auto &keys = idx_map[record];
    keys.erase(std::remove(keys.begin(), keys.end(), i), keys.end());
    if (keys.empty()) idx_map.erase(record);
    return true;
}

template <typename Key, typename Data>
vector<Key> Index<Key, Data>::find(string record) {
    if (idx_map.count(record) == 0) return vector<Key>();
    return idx_map[record];
}



template <typename Key, typename Data>
void Database<Key, Data>::insert(Data info, Key key) {
    table[key] = info;
    for (auto &item : indices) {
        item.second.insert(info, key);
    }
}

template <typename Key, typename Data>
void Database<Key, Data>::remove(Key key) {
    Data info = table[key];
    table.erase(key);
    for (auto &item : indices) {
        item.second.remove(info, key);
    }
}

template <typename Key, typename Data>
Data Database<Key, Data>::find(Key key) {
    if (table.count(key) == 0) return Data();
    return table[key];
}

template <typename Key, typename Data>  
vector<Data> Database<Key, Data>::find(string record_name, string record_value) {
    if (indices.count(record_name) == 0) return vector<Data>();
    auto keys = indices[record_name].find(record_value);
    vector<Data> result;
    for (auto key : keys) {
        result.push_back(table[key]);
    }
    return result;
}

template <typename Key, typename Data>
bool Database<Key, Data>::update(string record_name, Data new_info, Key key) {
    if (table.count(key) == 0) return false;
    if(indices.count(record_name) != 0) {
        auto &index = indices[record_name];
        if (!index.remove(table[key], key)) return false;
        index.insert(new_info, key);
    }
    if (!is_committed) 
        undo_logs.push_back({record_name, key, table[key]});
    table[key] = new_info;
    return true;
}

template <typename Key, typename Data>
int Database<Key, Data>::size() {
    return table.size();
}

template <typename Data, typename Key>
bool Iterator<Data, Key>::has_next() {
    return it != table.end();
}

template <typename Data, typename Key>
Data Iterator<Data, Key>::next() {
    return (it++)->second;
}

template <typename Key, typename Data>
Iterator<Data, Key> Database<Key, Data>::iterator() {
    return Iterator<Data, Key>(table);
}

template <typename Key, typename Data>
void Database<Key, Data>::commit() {
    undo_logs.clear();
}

template <typename Key, typename Data>
void Database<Key, Data>::rollback() {
    is_committed = true;
    for (auto &item : undo_logs) {
        update(item.record_name, item.old_info, item.key);
    }
    undo_logs.clear();
    is_committed = false;
}

template <typename Key, typename Data>
vector<Data> Database<Key, Data>::findall() {
    vector<Data> result;
    for (auto &item : table) {
        result.push_back(item.second);
    }
    return result;
}

#endif
