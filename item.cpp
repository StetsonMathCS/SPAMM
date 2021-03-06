#include <sstream>
#include "item.h"
#include "database.h"
#include "common.h"
using namespace std;

Item::Item(string n, string d, string o, ITEM_TYPE t) : name(n), desc(d), owner(o), type(t)
{
    name = n;
    desc = d;
    owner = o;
    type = t;
    itemId = -1;
}

void Item::save()
{
    //Have a list of the data, new lines should make it easier to read and load later
    
    if(itemId == -1) {
        itemId = db->lastid;
        string temp = "item\n name:"+getName()+"\n"+"desc:"+getDesc()+"\n"+"owner:"+getOwner()+"\n"+"type:"+to_string(getType());
        db->write(to_string(itemId),temp); 
        db->increment_lastid();
        db->addItem(this);
    }
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
