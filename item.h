#ifndef ITEM_H
#define ITEM_H
using namespace std;
#include <string>

class Room;

enum ITEM_TYPE {UNIQUE, PERPLAYER};

class Item
{
    private:
	std::string name; 
	std::string desc;

    public:
	Item(std::string, std::string);
	std::string getName() const;
	std::string getDesc() const;
};
#endif
