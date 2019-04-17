#include "item.h"
#include <iostream>

using namespace std;

std::string Item::getLongName()
{
    return longName;
}

void Item::setLongName(std::string name)
{
    longName = name;
}


