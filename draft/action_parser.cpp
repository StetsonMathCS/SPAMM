#include "parser.h"

#include <iostream>
using namespace std;

bool Parser::handleInput(Player* player, GameMap* gm)
{
    cout << "-> ";
    string command;
    cin >> command;
    if(command == "help")
    {
        cout << "Commands available:" << endl;
        cout << " -go [dir] (north, east, south, west)" << endl;
        cout << " -check (Check what items are in the room)" << endl;
        cout << " -inventory (See what items you have)" << endl;
        cout << " -get [object name](Pick up items)" << endl;
        cout << " -drop [object name] (Drop an item from your backpack)" << endl;
        cout << " -quit" << endl;
        cout << endl;
    } else if(command == "quit")
    {
        return false;
    } else if(command == "items")
    {
        if()
        {
            //check if player has items in their container
            cout << "It looks like your backpack is empty :(" << endl;
            cout << endl;
        } else
        {
            cout << "Your items: " << endl;
            //loop through items in the player's container
            for()
            {
                cout << "- "<< "get items" << endl;
            }
            cout << endl;
        }
    } else if(command == "go")
    {
        string direction;
        cin >> direction;
        //check direction
        if()
        {
            //get the container and if the container is empty
            if()
            {
                cout << "That's a dead end" << endl;
                cout << endl;
            } else
            {
                cout << "You're in " << "container name" << endl;
                cout << "container description" << endl;
                cout << endl;
            }
        } else
        {
            cout << "That's not a direction" << endl;
            cout << "Type 'help' for commands" << endl;
            cout << endl;
        }
    } else if(command == "check")
    {
        cout << "In " << "container" << endl;
        cout << "    " << "conatiner description" << endl;
        //check if there are items in container
        if()
        {
            cout << "There are no items in here " << endl;
            cout << endl;
        } else
        {
            cout << "Items in this room: " << endl;
            //loop through items in the room
            for()
            {
                cout << "- "<< "names of items in room" << endl;
            }
            cout << endl;
        }
    } else if(command == "get")
    {
        string object;
        cin >> object;
        //loop through items in room
        for()
        {
            //if the object entered matches an object in the container
            if()
            {
                cout << "You grabbed a " << object << endl;
                //call the method used to pickup
                //remove from container
                cout << endl;
            }
        }
    } else if(command == "drop")
    {
        string object;
        cin >> object;
        bool in = false;
        //check if that object is in the player container
        if()
        {
            cout << "There is no " << object << " in your inventory" << endl;
            cout << endl;
        } else
        {
            //loop through items in player's container
            for()
            {
                //if object name matches an item name in container
                if()
                {
                    cout << "You dropped a " << object << endl;
                    //add that item to current container
                    //remove from player container
                }
            }
            in = true;
        }
        if(!in)
        {
            cout << "You don't have a "<< object << " in your backpack." << endl;
        }
    } else
    {
        cout << "INCORRECT COMMAND, type 'help'" << endl;
    }
    return true;
}
