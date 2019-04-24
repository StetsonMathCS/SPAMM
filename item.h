#ifndef ITEM_H
#define ITEM_H
using namespace std;
#include <string>
#include "database.h"
class Room;

enum ITEM_TYPE {UNIQUE, PERPLAYER};

class Item
{
    private:
	std::string name; 
	std::string desc;
	std::string owner;
	ITEM_TYPE type;
    int itemId;

    public:
	Item(std::string, std::string, std::string, ITEM_TYPE);
	std::string getName() const;
	std::string getDesc() const;
	std::string getOwner() const;
    int getItemId() const;
	ITEM_TYPE getType();
	void setName(string);
	void setDesc(string);
	void setOwner(string);
	void setType(ITEM_TYPE);
    void setItemId(int);
    void save(int id); //writes item to redis
};
#endif
