#include "action_parser.h"
#include "database.h"
#include "game_server.h"
#include "common.h"
#include <iostream>
using namespace std;

class Player;
class Room;
class Item;
class Server;

Player *player;
Room *room;
Item *item;
Server *server;

void ActionParser::handleInput(int id, string command)
{
    if(command == "help")
    {
        server->printToUser(id, "Commands available:");
        server->printToUser(id, " -go [dir] (north, east, south, west)");
        server->printToUser(id, " -check (Check what items are in the room)");
        server->printToUser(id, " -inventory (See what items you have)");
        server->printToUser(id, " -get [object name](Pick up items)");
        server->printToUser(id, " -drop [object name] (Drop an item from your backpack)");
        server->printToUser(id, " -quit");
        //server->printToUser(id, output) << endl;
    } else if(command == "quit")
    {
    } else if(command == "items")
    {
        //if(false)
        if(player->listInventory() == NULL)
        {
            //check if player has items in their container
            server->printToUser(id, "It looks like your backpack is empty :(");
            //server->printToUser(id, output) << endl;
        } else
        {
            server->printToUser(id, "Your items: ");
            //loop through items in the player's container
            //for(int i = -1; i > 0;)
            //server->printToUser(id, "- " + player->listInventory());
            //server->printToUser(id, outpout);
        }
    } else if(command == "go")
    {
        //check direction
        if(false)
        {
            //get the container and if the container is empty
            if(false)
            {
                server->printToUser(id, "That's a dead end");
                //server->printToUser(id, output) << endl;
            } else
            {
                server->printToUser(id, "You're in container name");
                server->printToUser(id, "container description");
                //server->printToUser(id, output) << endl;
            }
        } else
        {
            server->printToUser(id, "That's not a direction");
            server->printToUser(id, "Type 'help' for commands");
            //server->printToUser(id, output) << endl;
        }
    } else if(command == "check")
    {
        server->printToUser(id, "In " + room->getTitle());
        server->printToUser(id, room->getDesc());
        //check if there are items in container
        //if(false)
        if(room->listItemsOnFloor().empty())
        {
            server->printToUser(id, "There are no items in here ");
            //server->printToUser(id, output) << endl;
        } else
        {
            server->printToUser(id, "Items in this room: ");
            //loop through items in the room
            //for(int i = -1; i > 0;)
            //server->printToUser(id, "- " + room->listItemsOnFloor());
            //server->printTouser(id, output);
        }
    } else if(command == "get")
    {
        //loop through items in room
        //for(int i = -1; i > 0;)
        for(room->listItemsOnFloor())
        {
            //if the object entered matches an object in the container
            //if(false)
                server->printToUser(id, "You grabbed a " + item->getName());
                //call the method used to pickup
                //remove from container
                //server->printToUser(id, output) << endl;
        }
    } else if(command == "drop")
    {
        bool in = false;
        //check if that object is in the player container
        //if(false)
        if(player->isItemInInventory() == false)
        {
            server->printToUser(id, "There is no " + item->getName() + " in your inventory");
            //server->printToUser(id, output) << endl;
        } else
        {
            player->listInventory();
            //loop through items in player's container
            //for(int i = -1; i > 0;)
            //if object name matches an item name in container
            server->printToUser(id, "You dropped a " + item->getName());
            //add that item to current container
            //remove from player container
            in = true;
        }
        if(!in)
        {
            server->printToUser(id, "You don't have a " + item->getName() " in your backpack.");
        }
    } else
    {
        server->printToUser(id, "INCORRECT COMMAND, type 'help'");
    }
}
