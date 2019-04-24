#include "action_parser.h"
#include "game_server.h"
#include <iostream>
using namespace std;

void ActionParser::handleInput(GameServer *server, int id, string command)
{
    if(command == "help")
    {
        server->printToUser(id, "Commands available:");
        server->printToUser(id, " -go [dir] (north, east, south, west)");
        //server->printToUser(id, output) << " -check (Check what items are in the room)" << endl;
        //server->printToUser(id, output) << " -inventory (See what items you have)" << endl;
        //server->printToUser(id, output) << " -get [object name](Pick up items)" << endl;
        //server->printToUser(id, output) << " -drop [object name] (Drop an item from your backpack)" << endl;
        //server->printToUser(id, output) << " -quit" << endl;
        //server->printToUser(id, output) << endl;
    } else if(command == "quit")
    {
    } else if(command == "items")
    {
        if(false)
        {
            //check if player has items in their container
            //server->printToUser(id, output) << "It looks like your backpack is empty :(" << endl;
            //server->printToUser(id, output) << endl;
        } else
        {
            //server->printToUser(id, output) << "Your items: " << endl;
            //loop through items in the player's container
            for(int i = -1; i > 0;)
            {
                //server->printToUser(id, output) << "- "<< "get items" << endl;
            }
            //server->printToUser(id, output) << endl;
        }
    } else if(command == "go")
    {
        //string direction;
        //cin >> direction;
        //check direction
        if(false)
        {
            //get the container and if the container is empty
            if(false)
            {
                //server->printToUser(id, output) << "That's a dead end" << endl;
                //server->printToUser(id, output) << endl;
            } else
            {
                //server->printToUser(id, output) << "You're in " << "container name" << endl;
                //server->printToUser(id, output) << "container description" << endl;
                //server->printToUser(id, output) << endl;
            }
        } else
        {
            //server->printToUser(id, output) << "That's not a direction" << endl;
            //server->printToUser(id, output) << "Type 'help' for commands" << endl;
            //server->printToUser(id, output) << endl;
        }
    } else if(command == "check")
    {
        //server->printToUser(id, output) << "In " << "container" << endl;
        //server->printToUser(id, output) << "    " << "conatiner description" << endl;
        //check if there are items in container
        if(false)
        {
            //server->printToUser(id, output) << "There are no items in here " << endl;
            //server->printToUser(id, output) << endl;
        } else
        {
            //server->printToUser(id, output) << "Items in this room: " << endl;
            //loop through items in the room
            for(int i = -1; i > 0;)
            {
                //server->printToUser(id, output) << "- "<< "names of items in room" << endl;
            }
            //server->printToUser(id, output) << endl;
        }
    } else if(command == "get")
    {
        //string object;
        //cin >> object;
        //loop through items in room
        for(int i = -1; i > 0;)
        {
            //if the object entered matches an object in the container
            if(false)
            {
                //server->printToUser(id, output) << "You grabbed a " << object << endl;
                //call the method used to pickup
                //remove from container
                //server->printToUser(id, output) << endl;
            }
        }
    } else if(command == "drop")
    {
        //string object;
        //cin >> object;
        bool in = false;
        //check if that object is in the player container
        if(false)
        {
            //server->printToUser(id, output) << "There is no " << object << " in your inventory" << endl;
            //server->printToUser(id, output) << endl;
        } else
        {
            //loop through items in player's container
            for(int i = -1; i > 0;)
            {
                //if object name matches an item name in container
                if(false)
                {
                    //server->printToUser(id, output) << "You dropped a " << object << endl;
                    //add that item to current container
                    //remove from player container
                }
            }
            in = true;
        }
        if(!in)
        {
            //server->printToUser(id, output) << "You don't have a "<< object << " in your backpack." << endl;
        }
    } else
    {
        //server->printToUser(id, output) << "INCORRECT COMMAND, type 'help'" << endl;
    }
}
