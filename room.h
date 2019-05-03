#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <set>
#include "item.h"

class Item;

class Room {
    private:
        std::string requirement;
        std::string title;
        std::string desc;
        std::map<std::string, Room*> exits;
        std::set<Item*> floor;
        int roomId;
    public:
        void save();
        void setTitle(std::string t){title = t;}
        Room(std::string, std::string);
        Room(std::string, std::string, std::string);
        std::string getRequirement() const;
        std::string getTitle() const;
        std::string getDesc() const;
        void setAdjacent(std::string, Room*);
        Room *getAdjacent(std::string);
        std::map<std::string, Room*> getExits() const;
        void addItemToFloor(Item*);
        std::set<Item*> getFloor() const;
        Item* findItemOnFloor(std::string) const;
        void listItemsOnFloor() const;
        void setReq(std::string);
        void setDesc(std::string);
        void setreqMove(std::string, std::string, std::string);
        void setChance(std::string, double, std::string);
        bool roomhaveReq();
};

#endif

