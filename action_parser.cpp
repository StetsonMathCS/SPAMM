#include "action_parser.h"
#include "database.h"
#include "game_server.h"
#include "common.h"
#include <iostream>
#include "room.h"
#include "item.h"
using namespace std;


void ActionParser::handleInput(Player *p, string command)
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
        //server->printToUser(p, output) << endl;
    } else if(command == "quit")
    {
    } else if(command == "items")
    {
        if(false) {// !p->listInventory().empty())
            //check if player has items in their container
            server->printToUser(p, "It looks like your backpack is empty :(");
            //server->printToUser(p, output) << endl;
        } else
        {
            server->printToUser(p, "Your items: ");
            //loop through items in the player's container
            //for(int i = -1; i > 0;)
            //server->printToUser(p, "- " + player->listInventory());
            //server->printToUser(p, outpout);
        }
    } else if(command.find("go ") == 0)
    {
        cout << "Direction to go: " << command.substr(3) << endl;
        //check direction
        if(p->getRoom() != NULL) 
        {
            Room *adj = p->getRoom()->getAdjacent(command.substr(3)); 
            //get the container and if the container is empty
            if(adj == NULL)
            {   
                cout << p->getUsername() << " tried to go a dead end in dir " << command.substr(3) << endl;
                server->printToUser(p, "That's a dead end");
                //server->printToUser(p, output) << endl;
            } else
            {
                cout << "SUCCESS" << endl;
                if(p->getRoom()->roomhaveReq() && p->reqisPassed())
                {
                server->printToUser(p, p->getRoom()->getTitle()); 
                server->printToUser(p, p->getRoom()->getDesc()); 
                //server->printToUser(p, output) << endl;
                }       
            }

        } else
        {
            server->printToUser(p, "That's not a direction");
            server->printToUser(p, "Type 'help' for commands");
            //server->printToUser(p, output) << endl;
        }
    } else if(command == "check")
    {
        server->printToUser(p, "In " + p->getRoom()->getTitle());
        server->printToUser(p, p->getRoom()->getDesc());
        //check if there are items in container
        //if(false)
        if(false) //if(p->getRoom()->listItemsOnFloor().empty())
        {
            server->printToUser(p, "There are no items in here ");
            //server->printToUser(p, output) << endl;
        } else
        {
            server->printToUser(p, "Items in this room: ");
            //loop through items in the room
            //for(int i = -1; i > 0;)
            //server->printToUser(p, "- " + room->listItemsOnFloor());
            //server->printTouser(id, output);
        }
    } else if(command == "get")
    {
        //loop through items in room
        for(int i = -1; i > 0;)
        //for(p->getRoom()->listItemsOnFloor())
        {
            //if the object entered matches an object in the container
            //if(false)
            //    server->printToUser(p, "You grabbed a " + item->getName());
                //call the method used to pickup
                //remove from container
                //server->printToUser(p, output) << endl;
        }
    } else if(command == "drop")
    {
        bool in = false;
        //check if that object is in the player container
        if(false)
        // Pass in item name: if(p->isItemInInventory() == false)
        {
           // server->printToUser(p, "There is no " + item->getName() + " in your inventory");
            //server->printToUser(p, output) << endl;
        } else
        {
            //p->listInventory();
            //loop through items in player's container
            //for(int i = -1; i > 0;)
            //if object name matches an item name in container
            //server->printToUser(p, "You dropped a " + item->getName());
            //add that item to current container
            //remove from player container
            in = true;
        }
        if(!in)
        {
            server->printToUser(p, "You don't have a BLANK in your backpack.");
        }
    }
}
