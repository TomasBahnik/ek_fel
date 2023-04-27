#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "main.hpp"

#define LIST "list"
#define FIND "find"
#define ERASE "erase"
#define REMOVE "remove"
#define SORT "sort"
#define NAME "name"
#define YEAR "year"
#define ID "id"

int get_number_of_digits(int i) {
    return i > 0 ? (int) log10((double) i) + 1 : 1;
}

// table functions

void print_border_basic() { std::cout << "+" << std::string(58, '-') << "+\n"; }

void print_border_cross() { std::cout << "+" << std::string(4, '-') << "+" << std::string(53, '-') << "+\n"; }

void stick_space_stick() { std::cout << "|" << std::setw(6) << "| "; }

void stick_numb_stick(int number) { std::cout << "|" << std::setw(3) << number << " | "; }

void print_header(std::string text) {
    print_border_basic();
    std::cout << "| " << text << std::setw(59 - text.size()) << "|\n";
    print_border_cross();
}

void print_end(int counter) {
    std::cout << "| Total: " << counter << std::setw(52 - get_number_of_digits(counter)) << "|\n";
    print_border_basic();
}

void Journal::print_item() {
    Item::print_item();
    unsigned int Journal_size = Journal::year.size() + Journal::volume.size() + Journal::issue.size();
    stick_numb_stick(Journal::id);
    std::cout << Journal::name << std::setw(54 - Journal::name.size()) << "|\n";
    stick_space_stick();
    std::cout << Journal::year << ", " << Journal::volume << "(" << Journal::issue << ")"
              << std::setw(50 - Journal_size) << "|\n";
    print_border_cross();

}

// list functions
void Book::print_item() {
    Item::print_item();
    stick_numb_stick(Book::id);
    std::cout << Book::name << std::setw(54 - Book::name.size()) << "|\n";
    stick_space_stick();
    std::cout << Book::year << ", " << Book::author << std::setw(52 - (Book::year.size() + Book::author.size()))
              << "|\n";
    print_border_cross();
}

// find functions
bool Journal::find_item(std::string arg) {
    std::stringstream parsed;
    parsed << name << "," << year << "," << volume << "," << issue;
    if (parsed.str().find(arg) != std::string::npos) {
        return true;
    }
    return false;
}

bool Book::find_item(std::string arg) {
    std::stringstream parsed;
    parsed << name << "," << year << "," << author;
    if (parsed.str().find(arg) != std::string::npos) {
        return true;
    }
    return false;
}
bool Journal::get_id(int arg){
    return arg == id;
}
bool Book::get_id(int arg){
    return arg == id;
}

Database::Database() {
    // Database constructor
}

Database::~Database() {
    for (auto i = db.begin(); i != db.end(); i++)
        delete *i;
    db.clear();
}

// add item to the database
void Database::add(Item *a) {
    db.push_back(a);
}

// definition of the sort function according to name
bool sort_name::operator()(const Item *a, const Item *b) {
    return false;
}

int Database::size() {
    return db.size();
}


void Database::list() {
    int cnt = 0;
    print_header("List of all records");
    for (Item *item: db) {
        item->print_item();
        cnt++;
    }
    print_end(cnt);
}

void Database::find(std::string argument) {
    int cnt = 0;
    print_header("Search for \"" + argument + "\"");
    for (Item *item: db) {
        if (item->find_item(argument)) {
            item->print_item();
            cnt++;
        }
    }
    print_end(cnt);
}

void Database::erase(std::string argument) {
    bool item_found = true;
    while (item_found) {
        item_found = false;
        for (int i = 0; i < (int) db.size(); ++i) {
            if (db[i]->find_item(argument)) {
                db.erase(db.begin() + i);
                item_found = true;
            }
        }
    }
}

void Database::remove(std::string argument) {
    for (int i = 1; i < (int) db.size(); ++i) {
        if (db[i]->get_id(std::stoi(argument))) {
            db.erase(db.begin() + i);
        }
    }
}

void Database::sort(std::string argument, std::string order) {
    if (argument == YEAR) {
        if (order == "desc") {
            std::sort(db.begin(), db.end(), [](const Item *a, const Item *b) {
                return a->year > b->year;
            });
        } else {
            std::sort(db.begin(), db.end(), [](const Item *a, const Item *b) {
                return a->year < b->year;
            });
        }
    } else if (argument == NAME) {
        if (order == "desc") {
            std::sort(db.begin(), db.end(), [](const Item *a, const Item *b) {
                return a->name > b->name;
            });
        } else {
            std::sort(db.begin(), db.end(), [](const Item *a, const Item *b) {
                return a->name < b->name;
            });
        }
    } else if (argument == ID) {
        if (order == "desc") {
            std::sort(db.begin(), db.end(), [](const Item *a, const Item *b) {
                return a->id > b->id;
            });
        } else {
            std::sort(db.begin(), db.end(), [](const Item *a, const Item *b) {
                return a->id < b->id;
            });
        }


    }

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
    int size_of_dat = db.size();
    while (std::getline(std::cin, a)) {
        size_t position;
        if ((position = a.find(':')) == std::string::npos) {
            if (a == LIST) {
                db.list();
            }
                // error handling
            else if ((a == FIND) || (a == ERASE) || (a == REMOVE)) {
                print_border_basic();
                std::cout << "| Command \"" + a.substr(0, position) + "\" expects some argument"
                          << std::setw(27 - a.size())
                          << "|\n";
                print_border_basic();
            } else if (a == SORT) {
                print_border_basic();
                std::cout << "| Unknown sorting order" << std::setw(38) << "|\n";
                print_border_basic();
            } else {
                print_border_basic();
                std::cout << "| Unknown command \"" + a.substr(0, position) + "\"" << std::setw(41 - a.size()) << "|\n";
                print_border_basic();
            }
        } else {
            std::string command = a.substr(0, position);
            std::string argument = a.substr(position + 1);
            if (command == FIND) {
                db.find(argument);
            } else if (command == ERASE) {
                db.erase(argument);
            } else if (command == REMOVE) {
                if (std::stoi(argument) > size_of_dat) {
                    print_border_basic();
                    std::cout << "| ID = " << std::stoi(argument) << " is not in the database"
                              << std::setw(38 - a.size()) << "|\n";
                    print_border_basic();
                    size_of_dat--;
                } else
                    db.remove(argument);
            } else if (command == SORT) {
                if ((position = argument.find(':')) == std::string::npos) {
                    db.sort(argument, "asc"); //vzestupne
                } else {
                    std::string argument_sort = argument.substr(0, position);
                    db.sort(argument_sort, "desc"); //sestupne
                }
            } else {
                std::cout << "Unknown command\n";
            }
        }
    }
    return 0;
}


