#include <iostream>
#include "room.h"
#include "common.h"
#include "database.h"

using namespace std;

Room::Room(string t, string d){
    title = t;
    desc = d;
    roomId = -1;
    requirement == "No Req";
}
Room::Room(string t, string d, string r){
    title = t;
    desc = d;
    roomId = -1;
    requirement = r;
}
void Room::save(){
    string temp;
    if(roomId == -1){
        roomId = db->lastid;
        temp = "room \n title:"+getTitle()+"\n"+"desc:"+getDesc()+"\n";
        db->write(to_string(roomId),temp);
        db->increment_lastid();
        db->addRoom(this);
    }
}
string Room::getRequirement() const {
    return requirement;
}
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

void Room::dropItemFromFloor(Item* item) {
    floor.erase(item);
}

set<Item*> Room::getFloor() const {
    return floor;
}

set<Item*> Room::getItems() const {
    return floor;
}

Item* Room::findItemOnFloor(std::string name) const {
    set<Item*>::const_iterator p;
    for(p = floor.begin(); p != floor.end(); p++) {
        if ((*p)->getName() == name) {
            return *p;
        }
    }
    cout << "ERROR: Item not found." << endl;
    return NULL;
}

void Room::listItemsOnFloor() const {
        set<Item*>::const_iterator p;
        cout << "You scan the room and try to find anything useful." << endl;
        /*
        if (roomSet.size() == 0) {
            cout << "There are no useful items in this room." << endl;
        } else {
            cout << "You can make out the faint out lines of the following items: " << endl;
            for (p = floor.begin(); p != floor.end(); p++){
                cout << (*p)->getName() << endl;
            }
        }
        */
}
void Room::setReq(string req)
{
    string title = this->getTitle();
    string description = this->getDesc();

    Room(title, description, req);
}
void Room::setDesc(string description)
{
    string req = this->getRequirement(); 
    string title = this->getTitle();
    
    if(roomhaveReq())
    {
        Room(title, description, req);    
    }
    else
    {
        Room(title, description);
    }
}
void Room::setreqMove(string oldroom, string req, string newroom)
{
    if(this->roomhaveReq())
    {
                
    }
    
}
void Room::setChance(string oldRoom, double chance, string newroom)
{
    
}

bool Room::roomhaveReq()
{
    if(this->getRequirement() == "No Req")
    {
        return false;
    }
    else
    {
        return true;
    }
}
