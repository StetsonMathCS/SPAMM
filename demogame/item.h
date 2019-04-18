#ifndef ITEM_H
#define ITEM_H

#include <vector>
#include <string>

class Item {
    private:
        std::string longName;
        std::string description;
    public:
        std::string getLongName();
        void setLongName(std::string);
        
};

#endif

