#include "player.h"
#include "room.h"
#include "container.h"
#include <iostream>
#include <regex>
using namespace std;

void Player::setCurrentContainer(Container* room)
{
    currentContainer = room;   
}

Container* Player::getCurrentContainer()
{
    return currentContainer;
}

void Player::move(std::string& dir, GameMap& gm)
{
    currentContainer = gm.getGameMap()[currentContainer][dir];        
}

Container* Player::getItems()
{
    return items;
}

void Player::pickup(Item* item)
{
    getItems()->addToContainer(item);    
}

