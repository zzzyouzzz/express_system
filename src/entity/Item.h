#ifndef ITEM_H
#define ITEM_H
#include <string>
using namespace std;
class Item{   
    public:
        enum ItemType{
            commonItem,
            fragileItem,
            bookItem
        };
        Item(ItemType type, string name) : type(type), name(name) {};
        ItemType get_type() {
            return type;
        };
        string get_name() {
            return name;
        };
        virtual int get_price() = 0;
    protected:        
        ItemType type;
        string name;
};
class CommonItem : public Item{
    public:
        CommonItem(string name) : Item(commonItem, name) {};
        int get_price() override {
            return 5;
        };
};
class FragileItem : public Item{
    public:
        FragileItem(string name) : Item(fragileItem, name) {};
        int get_price() override {
            return 10;
        };
};
class BookItem : public Item{
    public:
        BookItem(string name) : Item(bookItem, name) {};
        int get_price() override {
            return 15;
        };
};
#endif