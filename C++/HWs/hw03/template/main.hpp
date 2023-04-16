#include <vector>
#include <string>

#ifndef __MAIN_HPP__
#define __MAIN_HPP__

struct sort_name;

class Item {
	protected:
		int ID;
		std::string name, year;
	public:
		Item (std::string a, std::string b);
		virtual ~Item ();
		friend sort_name;
};

// Book related to the Database
class Book{

};

// Journal related to the Database
class Journal{

};

// declaration of the sort function according to name
struct sort_name {
	inline bool operator() (const Item *a, const Item * b);
};

class Database {
	private:
		std::vector<Item *> db;
	public:
		Database ();
		Database::~Database();
		void add(Item * a);
};

#endif // __MAIN_HPP__