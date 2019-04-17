#include "item.h"
using namespace std;

Item::Item(string n, string d) : name(n), desc(d)
{
    name = n;
    desc = d;
}

string Item::getName() const
{
    return name;
}

string Item::getDesc() const
{
    return desc;
}
