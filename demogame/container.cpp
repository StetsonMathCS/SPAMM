#include "container.h"
#include <iostream>

using namespace std;

void Container::setDescription(std::string desc)
{
    description = desc;
}

std::string Container::getDescription()
{
    return description;
}

void Container::setName(std::string n)
{
    name = n;
}

std::string Container::getName()
{
    return name;
}
std::vector<Item*> Container::getItemsInContainer()
{
   return itemsInContainer;
}

void Container::addToContainer(Item* t)
{
    itemsInContainer.push_back(t);
}

void Container::removeFromContainer(Item* item)
{
    for(unsigned int i = 0; i < itemsInContainer.size(); i++)
    {
        if(item->getLongName() == itemsInContainer.at(i)->getLongName())
        {
            std::swap(itemsInContainer.at(i), itemsInContainer.back());
            itemsInContainer.pop_back();
        }
    }
}
