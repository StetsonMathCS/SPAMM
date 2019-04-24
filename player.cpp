#include "player.h"
#include "room.h"
#include "game_server.h"
#include <iterator>
#include <iostream>

class GameServer;

using namespace std;

Player::Player() {
    
}

Player::Player(string name, string desc) {
    username = name;
    description = desc;
}

void Player::setRoom(Room* r) {
    room = r;
}

Room* Player::getRoom() const {
     return room;
}

void Player::listInventory() const {
    set<Item*>::const_iterator p;
    cout << "\nInventory: " << endl;
    for (p = inventory.begin(); *p != NULL; p++){
        cout << (*p)->getName() << endl;
    }
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
