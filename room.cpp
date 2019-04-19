#include "room.h"

using namespace std;

Room::Room(string t, string d)
    : title(t), desc(d) {}

string Room::getTitle() const {
    return title;
}

string Room::getDesc() const {
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

map<string, Room*> Room::getExits() const {
    return exits;
}

void Room::addItemToFloor(Item* item) {
    floor.insert(item);
}

set<Item*> Room::getFloor() const {
    return floor;
}

Item* Room::findItemOnFloor(std::string) const {
    set<Item*>::const_iterator p;
    for(p = floor.begin(); p != floor.end(); p++) {
        if ((*p)->getName() == name) {
            return *p;
        }
    }
    cout << "ERROR: Item not found." << endl;
    return NULL;
}

void Room::listItemsOnFloor() {
        set<Item*>::const_iterator p;
        cout << "You scan the room and try to find anything useful." << endl;
        if (roomSet.size() == 0) {
            cout << "There are no useful items in this room." << endl;
        } else {
            cout << "You can make out the faint out lines of the following items: " << endl;
            for (p = floor.begin(); p != floor.end(); p++){
                cout << (*p)->getName() << endl;
            }
        }
}
