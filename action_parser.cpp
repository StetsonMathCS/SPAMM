#include "action_parser.h"
#include "database.h"
#include "game_server.h"
#include "common.h"
#include <iostream>
#include "room.h"
#include "item.h"
using namespace std;


bool ActionParser::handleInput(Player *p, string command)
{
    if(command == "help")
    {
        server->printToUser(p, "Commands available:");
        server->printToUser(p, " -go [dir] (north, east, south, west)");
        server->printToUser(p, " -check (Check what items are in the room)");
        server->printToUser(p, " -inventory (See what items you have)");
        server->printToUser(p, " -get [object name](Pick up items)");
        server->printToUser(p, " -drop [object name] (Drop an item from your backpack)");
        server->printToUser(p, " -quit");
        return false;
    } else if(command.find("inventory ") == 0)
    {
        if(p->getInventory().empty()) {
            //check if player has items in their container
            server->printToUser(p, "It looks like your backpack is empty :(");
        } else
        {
            server->printToUser(p, "Your items: ");
            //loop through items in the player's container
            set<Item*>::iterator it;
            auto inventory = p->getInventory();
            for(it = inventory.begin(); it != inventory.end(); it++)
            {
                server->printToUser(p, "- " + (*it)->getName());
            }
        }

        return true;
    } else if(command.find("go ") == 0)
    {
        server->printToUser(p, "Direction to go: " + command.substr(3));
        //check direction
        if(p->getRoom() != NULL) 
        {
            Room *adj = p->getRoom()->getAdjacent(command.substr(3)); 
            //get the container and if the container is empty
            if(adj == NULL)
            {   
                server->printToUser(p, p->getUsername() + " tried to go a dead end in dir " + command.substr(3));
                server->printToUser(p, "That's a dead end");
                //server->printToUser(p, output) << endl;
            } else
            {
                server->printToUser("SUCCESS");
                if(p->getRoom()->roomhaveReq() && p->reqisPassed())
                {
		    p->setRoom(adj);
                    server->printToUser(p, "You're in " + p->getRoom()->getTitle());
                    server->printToUser(p, p->getRoom()->getDesc());
                    //server->printToUser(p, p->getRoom()->getDesc()); 
                } else if (!p->getRoom()->roomhaveReq()){
                    p->setRoom(adj);
                } else {
                    server->printToUser(p, "Cannot go this way.");
                }       
            }

        return true;
        } else
        {
            server->printToUser(p, "That's not a direction");
            server->printToUser(p, "Type 'help' for commands");
            return true;
        }
    } else if(command.find("check ") == 0)
    {
        server->printToUser(p, "In " + p->getRoom()->getTitle());
        server->printToUser(p, p->getRoom()->getDesc());
        //check if there are items in container
        if(p->getRoom()->getItems().empty())
        {
            server->printToUser(p, "There are no items in here ");
            return true;
        } else
        {
            server->printToUser(p, "Items in this room: ");
            //loop through items in the room
            set<Item*>::iterator it;
            auto items = p->getRoom()->getItems();
            for(it = items.begin(); it != items.end(); it++)
            {
                server->printToUser(p, "- " + (*it)->getName());
            }
            return true;
        }
    } else if(command.find("get ") == 0)
    {
        //loop through items in room
        auto items = p->getRoom()->getItems();
        set<Item*>::iterator it;
        for(it = items.begin(); it != items.end(); it++)
        {
            //TODO change findItemOnFloor
            if(p->getRoom()->findItemOnFloor("command") != NULL)
            {
                server->printToUser(p, "You grabbed a ");
                p->addItemToInventory(*it);
                p->getRoom()->dropItemFromFloor(*it);
            return true;
            }
        }
            return true;
    } else if(command.find("drop ") == 0)
    {
        bool in = false;
        // Pass in item name: if(p->isItemInInventory() == false)
        //TODO put something in there after user types command
        if(p->isItemInInventory("command") == false)
        {
            //TODO fix what the user puts in for item in command
            server->printToUser(p, "There is no command in your inventory");
           // server->printToUser(p, "There is no " + item->getName() + " in your inventory");
            return true;
        } else
        {
            set<Item*>::iterator it;
            auto inventory = p->getInventory();
            for(it = inventory.begin(); it != inventory.end(); it++)
            {
                if((*it)->getName() == "command")
                {
                    server->printToUser(p, "You dropped a ");
                    p->getRoom()->addItemToFloor(*it);
                    p->dropItem((*it)->getName());
                }
            }
            in = true;
            return true;
        }
        if(!in)
        {
            server->printToUser(p, "You don't have a BLANK in your backpack.");
        }
    }
    return false;
}
