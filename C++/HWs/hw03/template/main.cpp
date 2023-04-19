#include <iostream>
#include <sstream>
#include <algorithm>
#include "main.hpp"

Database::Database() {
    // Database constructor
}

// add item to the database
void Database::add(Item *a) {
    db.push_back(a);
}

// definition of the sort function according to name
bool sort_name::operator()(const Item *a, const Item *b) {
    return false;
}


Database::~Database() {
    for (auto i = db.begin(); i != db.end(); i++)
        delete *i;
    db.clear();
}

// todo solve saving ID in Item
//Item item;
void Database::list() {
    std::cout << "list\n";
    for (Item *item : db) {
        item->print_item(); //todo add function to Item and declarate in book + journal
    }
}

void Database::find(std::string basicString) {
    std::cout << "find\n";
}

void Database::erase(std::string basicString) {
    std::cout << "erase\n";
}

void Database::remove(std::string basicString) {
    std::cout << "remove\n";
}

void Database::sort(std::string basicString, const char *stringos) {
    std::cout << "sort\n";
}

int main() {
    Database db;
    db.add(new Journal("IEEE Transaction on Computers", "C-35", "10", "1986"));
    db.add(new Journal("IEEE Transaction on Computers", "C-35", "11", "1986"));
    db.add(new Journal("IEEE Transactions on Communications", "28", "8", "1980"));
    db.add(new Book("Dva roky prazdnin", "Jules Verne", "1888"));
    db.add(new Book("Tajuplny ostrov", "Jules Verne", "1874"));
    db.add(new Book("Ocelove mesto", "Jules Verne", "1879"));
    std::string a;
    while (std::getline(std::cin, a)) {
        size_t position;
        if ((position = a.find(":")) == std::string::npos) {
            if (a == "list")
                db.list();
            else {
                //todo error handling
            }
        } else {
            std::string command = a.substr(0, position);
            std::string argument = a.substr(position + 1);
            if (command == "find")
                db.find(argument);
            else if (command == "erase") {
                db.erase(argument);
            } else if (command == "remove") {
                db.remove(argument);
            } else {
                if ((position = argument.find(":")) == std::string::npos) {
                    db.sort(argument, "asc"); //vzestupne
                } else {
                    std::string argument_sort = argument.substr(0, position);
                    db.sort(argument_sort, "asc"); //sestupne
                }
            }
        }
    }
    return 0;
}