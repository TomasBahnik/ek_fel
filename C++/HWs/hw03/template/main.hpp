#include <utility>
#include <vector>
#include <string>
//#include <iostream>

#ifndef __MAIN_HPP__
#define __MAIN_HPP__

struct sort_name;

class Item {
protected:
    static int count;
public:
    std::string name;
    std::string year;
    int id;

    Item(std::string name, std::string year) : name(name), year(year) {
        id = count ++;
    };

    virtual ~Item();

    friend sort_name;

    virtual void print_item() = 0;

    virtual bool find_item(std::string arg) = 0;
};
int Item::count = 1;
Item::~Item() {}
void Item::print_item() {}

// Book related to the Database
class Book : public Item {
public:
    Book(std::string name, std::string author, std::string year)
            : Item(std::move(name), std::move(year)), author(std::move(author)) {}

private:
    std::string author;
    void print_item() override;
    bool find_item(std::string arg) override;
//    void remove_item(int arg) override;
};

// Journal related to the Database
class Journal : public Item {
public:
    Journal(std::string name, std::string volume, std::string issue, std::string year)
            : Item(name, std::move(year)), volume(std::move(volume)), issue(std::move(issue)) {}

private:
    std::string volume;
    std::string issue;
    void print_item() override;
    bool find_item(std::string arg) override;
//    void remove_item(int arg) override;
};

// declaration of the sort function according to name
struct sort_name {
    inline bool operator()(const Item *a, const Item *b);
};

class Database {
private:
    std::vector<Item *> db;
public:
    Database();

    ~Database();

    void add(Item *a);

    void list();

    void find(std::string argument);

    void erase(std::string argument);

    void remove(std::string argument);

    void sort(std::string argument, std::string order);

    int size ();
};

#endif // __MAIN_HPP__