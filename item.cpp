#include "item.h"
using namespace std;

Item::Item(string n, string d, string o, ITEM_TYPE t) : name(n), desc(d), owner(o), type(t)
{
    name = n;
    desc = d;
    owner = o;
    type = t;
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
