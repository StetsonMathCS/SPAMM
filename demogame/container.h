#ifndef CONTAINER_H
#define CONTAINER_H

#include "item.h"
#include <vector>

class Container {
    private:
        std::vector<Item*> itemsInContainer;
        std::string description;
        std::string name;
    public:
        std::string getDescription();
        void setDescription(std::string);
        std::string getName();
        void setName(std::string);
        std::vector<Item*> getItemsInContainer();
        void addToContainer(Item*);
        void removeFromContainer(Item*);
};

#endif
