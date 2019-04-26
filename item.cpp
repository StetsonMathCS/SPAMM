#include <sstream>
#include "item.h"
#include "database.h"
using namespace std;

Item::Item(string n, string d, string o, ITEM_TYPE t) : name(n), desc(d), owner(o), type(t)
{
    name = n;
    desc = d;
    owner = o;
    type = t;
}

void Item::save(int id)
{
    //Have a list of the data, new lines should make it easier to read and load later
    string temp = "name:"+getName()+"\n"+"desc:"+getDesc()+"\n"+"owner:"+getOwner()+"\n"+"type:"+to_string(getType());
    Database *d = new Database();
    d->write(to_string(id),temp); 
    
    imcrement_lastid();

    //increment here, but I want to hold off on that for now

    delete d;
}

string Item::getName() const
{
    return name;
}

string Item::getDesc() const
{
    return desc;
}

string Item::getOwner() const
{
    return owner;
}

ITEM_TYPE Item::getType()
{
    return type;
}

int Item::getItemId() const
{
    return itemId;
}

void Item::setItemId(int id)
{
    itemId = id;
}

void Item::setName(string n)
{
    name = n;
}

void Item::setDesc(string d)
{
    desc = d;
}

void Item::setOwner(string o)
{
    owner = o;
}

void Item::setType(ITEM_TYPE t)
{
    type = t;
}
