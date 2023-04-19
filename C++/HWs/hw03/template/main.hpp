#include <utility>
#include <vector>
#include <string>
#include <iostream>

#ifndef __MAIN_HPP__
#define __MAIN_HPP__

struct sort_name;

class Item {
protected:
    int ID;
    std::string name, year;
public:
    Item(std::string name, std::string year) : name(name), year(year){};
    virtual ~Item();
    friend sort_name;
    virtual void print_item(){
    } //pure virtual function
};

Item::~Item() {
}
// Book related to the Database
class Book : public Item{
public:
    Book(std::string name, std::string author, std::string year)
    : Item(std::move(name), std::move(year)), author(std::move(author)) {}
private:
    std::string author;
    void print_item() override {
        Item::print_item();
        std::cout << name << " " << author << " " << year << "\n";
    }
};

// Journal related to the Database
class Journal : public Item{
public:
    Journal(std::string name, std::string volume, std::string issue, std::string year)
    : Item(name, std::move(year)), volume(std::move(volume)), issue(std::move(issue)) {}

private:
    std::string volume;
    std::string issue;
    void print_item() override {
        Item::print_item();
        std::cout << name << " " << volume << " " << issue << " " << year << "\n";
    }
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

    void find(std::string basicString);

    void erase(std::string basicString);

    void remove(std::string basicString);

    void sort(std::string basicString, const char *string);
};

#endif // __MAIN_HPP__