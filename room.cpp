#include "room.h"

using namespace std;

Room::Room(string t, string d)
    : title(t), desc(d) {}

string Room::getTitle() const
{
    return title;
}

string Room::getDesc() const
{
    return desc;
}

void Room::setAdjacent(string s, Room *r) {
    exits[s] = r;
}

Room *Room::getAdjacent(string s) {
    if(exits.find(s) != exits.end()) {
        return exits[s];
    } else {
        return NULL;
    }
}

set<Item*> Room::getSet() {
    return inventory;
}

map<string, Room*> Room::getExits() const {
    return exits;
}

