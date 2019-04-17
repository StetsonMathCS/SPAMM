#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <set>

class Item;

class Room {
    private:
        std::string title;
        std::string desc;
        std::map<std::string, Room*> exits;
    public:
        Room(std::string, std::string);
        std::string getTitle() const;
        std::string getDesc() const;
        void setAdjacent(std::string, Room*);
        Room *getAdjacent(std::string);
        std::set<Item*> getSet();
        std::map<std::string, Room*> getExits() const;
};

#endif

