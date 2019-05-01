#include "player.h"
#include "room.h"
#include "game_server.h"
#include <iterator>
#include <iostream>
#include "common.h"
#include "database.h"

using namespace std;

Player::Player() {
    
}

Player::Player(string name, string desc, int id) {
    username = name;
    description = desc;
    playerID = id;
}

void Player::save(){
    string temp;
    if(playerID == -1){
        db->increment_lastid();
        playerID = db->lastid;
        temp = "player \n username:"+getUsername()+"\n"+"desc:"+getDescription()+"\n";
        db->write(to_string(playerID),temp);
    }
}

set<Item*> Player::dropItem(string name) {
    set<Item*>::const_iterator p;
    set<Item*> newInventoryState;
    for (p = inventory.begin(); *p != NULL; p++){
        if (!((*p)->getName() == name)) {
            newInventoryState.insert(*p);    
        }
    }
    return newInventoryState;
}

void Player::setRoom(Room* r) {
    room = r;
}

Room* Player::getRoom() const {
     return room;
}

set<Item*> Player::getInventory() const {
    /*set<Item*>::const_iterator p;
    cout << "\nInventory: " << endl;
    for (p = inventory.begin(); *p != NULL; p++){
        cout << (*p)->getName() << endl;
    }*/
    return inventory;
}

void Player::addItemToInventory(Item* item) {
    inventory.insert(item);
}

Item* Player::findItemInInventory(string name) const {
    set<Item*>::const_iterator p;
    for(p = inventory.begin(); p != inventory.end(); p++) {
        if ((*p)->getName() == name) {
            return *p;
        }
    }
    cout << "ERROR: Item not found." << endl;
    return NULL;
}
bool Player::isItemInInventory(string name) {
    set<Item*>::const_iterator p;
    for(p = inventory.begin(); p != inventory.end(); p++) {
        if ((*p)->getName() == name) {
            return true;
        }
    }
    return false;
}
void Player::setCanBuild(bool permission) {
    canBuild = permission;
} 

bool Player::getCanBuild() const {
   return canBuild;
}

void Player::setUsername(string name) {
    username = name;
}

string Player::getUsername() const {
    return username;
}

void Player::setLastLoginIp(string ip) {
    lastLoginIp = ip;
}

string Player::getLastLoginIp() const {
    return lastLoginIp;
}

void Player::setLastLoginTime(string timestamp) {
    lastLoginTime = timestamp;
}

string Player::getLastLoginTime() const {
    return lastLoginTime;
}

void Player::setPassword(string pass) {
    password = pass;
}

string Player::getPassword() const {
    return password;
}

void Player::setDescription(string desc) {
    description = desc;
}

string Player::getDescription() const {
    return description;
}

void Player::setID(int id) {
    playerID = id;
}

int Player::getID() const {
    return playerID;
}

bool Player::reqisPassed()
{
    return true;
}
/*bool Player::connected() const {
    return true;
    //not needed as there is similar functionality in gameserver
}*/
