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
	std::string owner;
	ITEM_TYPE type;

    public:
	Item(std::string, std::string);
	std::string getName() const;
	std::string getDesc() const;
	std::string getOwner() const;
	ITEM_TYPE getType();
	void setName(string);
	void setDesc(string);
	void setOwner(string);
	void setType(ITEM_TYPE);
};
#endif
