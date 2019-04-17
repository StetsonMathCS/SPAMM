#include "player.h"
#include "room.h"
#include <iterator>
#include <iostream>
#include <regex>

using namespace std;

Player::Player() {
    
}

void Player::setRoom(Room* r) {
    room = r;
}

Room* Player::getRoom() {
     return room;
}

void Player::listInventory() const {
    set<Item*> newSet = inventory; 
    set<Item*>::const_iterator p;
    cout << "\nInventory: " << endl;
    for (p = newSet.begin(); *p != NULL; p++){
        cout << (*p)->getName() << endl;
    }
}
