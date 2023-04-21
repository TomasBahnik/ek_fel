#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "main.hpp"

int get_number_of_digits(int i) {
    return i > 0 ? (int) log10((double) i) + 1 : 1;
}

// table functions

void print_border_basic() { std::cout << "+" << std::string(58, '-') << "+\n"; };

void print_border_cross() { std::cout << "+" << std::string(4, '-') << "+" << std::string(53, '-') << "+\n"; };

void stick_space_stick() { std::cout << "|" << std::setw(6) << "| "; };

void stick_numb_stick(int number) { std::cout << "|" << std::setw(3) << number << " | "; };

void print_header(std::string text){
    print_border_basic();
    std::cout << "| " << text << std::setw(59 - text.size()) << "|\n";
    print_border_cross();
}

void print_end (int counter){
    std::cout << "| Total: " << counter << std::setw(52 - get_number_of_digits(counter)) << "|\n";
    print_border_basic();
}

void Journal::print_item() {
    Item::print_item();
    unsigned int Journal_size = Journal::year.size() + Journal::volume.size() + Journal::issue.size();
    stick_numb_stick(Journal::ID);
    std::cout << Journal::name << std::setw(54 - Journal::name.size()) << "|\n";
    stick_space_stick();
    std::cout << Journal::year << ", " << Journal::volume << "(" << Journal::issue << ")"
              << std::setw(50 - Journal_size) << "|\n";
    print_border_cross();

}

// list functions
void Book::print_item() {
    Item::print_item();
    stick_numb_stick(Book::ID);
    std::cout << Book::name << std::setw(54 - Book::name.size()) << "|\n";
    stick_space_stick();
    std::cout << Book::year << ", " << Book::author << std::setw(52 - (Book::year.size() + Book::author.size()))
              << "|\n";
    print_border_cross();
}

// find function
bool Journal::find_item(std::string arg) {
    std::stringstream parsed;
    parsed << name << "," << year << "," << volume << "," << issue;
    if (parsed.str().find(arg) != std::string::npos){
        return true;
    }
    return false;
}

bool Book::find_item(std::string arg) {
    std::stringstream parsed;
    parsed << name << "," << year << "," << author;
    if (parsed.str().find(arg) != std::string::npos){
        return true;
    }
    return false;
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
    print_header("Search for \""+ argument +"\"");
    for (Item *item: db) {
        if(item->find_item(argument)){
            item->print_item();
            cnt ++;
        }
    }
    print_end(cnt);
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

            else if ((a == "find") || (a == "erase") || (a == "remove")) {
                print_border_basic();
                std::cout << "| Command \"" << a.substr(0, position) << "\" expects some argument " << std::setw(20)
                          << "|\n";
                print_border_basic();
            } else {
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


