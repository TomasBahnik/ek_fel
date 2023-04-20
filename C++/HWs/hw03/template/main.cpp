#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "main.hpp"

//todo bool Journal::find_argument()

// list functions

void print_border_basic() { std::cout << "+" << std::string (58, '-') << "+\n"; };
void print_border_cross() { std::cout << "+" << std::string (4, '-') << "+" << std::string (53, '-') << "+\n"; };
void stick_space_stick() { std::cout << "|" << std::setw(6) << "| "; };
void stick_numb_stick(int number) { std::cout << "|" << std::setw(3) << number << " | "; };

void Journal::print_item() {
    Item::print_item();
    unsigned int Journal_size = Journal::year.size() + Journal::volume.size() + Journal::issue.size();
    stick_numb_stick(Journal::ID);
    std::cout << Journal::name << std::setw(54 - Journal::name.size()) << "|\n";
    stick_space_stick();
    std::cout << Journal::year << ", " << Journal::volume << "(" << Journal::issue << ")" << std::setw(50 - Journal_size) << "|\n";
    print_border_cross();

}

void Book::print_item() {
    Item::print_item();
    stick_numb_stick(Book::ID);
    std::cout << Book::name << std::setw(54 - Book::name.size()) << "|\n";
    stick_space_stick();
    std::cout << Book::year << ", " << Book::author << std::setw(52 - (Book::year.size() + Book::author.size())) << "|\n";
    print_border_cross();
}

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
void Database::list() {
    print_border_basic();
    std::cout << "| List of all records" << std::setw(40) << "|\n";
    print_border_cross();
    for (Item *item : db) {
        item->print_item();
    }
}

void Database::find(std::string argument) {
//    for(unsigned long i = 0; i < db.size(); ++i){
//        if(Journal[i]->name.find(argument) != std::string npos){
//            std::cout << "founded\n";
//        }
//    }
    std::cout << "find " << argument << "\n";
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
        if ((position = a.find(':')) == std::string::npos) {
            if (a == "list")
                db.list();

            else if ((a == "find") || (a == "erase") || (a == "remove")){
                print_border_basic();
                std::cout << "| Command \"" << a.substr(0, position) << "\" expects some argument " << std::setw(20) <<"|\n";
                print_border_basic();
            }
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
                if ((position = argument.find(':')) == std::string::npos) {
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


