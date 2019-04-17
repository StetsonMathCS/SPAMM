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
        cout << " -items (See what items you have)" << endl;
        cout << " -get [object name](Pick up items)" << endl;
        cout << " -drop [object name] (Drop an item from your backpack)" << endl;
        cout << " -quit" << endl;
        cout << endl;
    } else if(command == "quit") 
    {
        return false;
    } else if(command == "items") 
    {
        if(player->getItems()->getItemsInContainer().empty())
        {
            cout << "It looks like your backpack is empty :(" << endl;
            cout << endl;
        } else 
        {
            cout << "Your items: " << endl;
            for(unsigned int i = 0; i < player->getItems()->getItemsInContainer().size(); i++)
            {
                cout << "- "<< player->getItems()->getItemsInContainer().at(i)->getLongName() << endl;
            }
            cout << endl;
        }   
    } else if(command == "go") 
    {
        string direction;
        cin >> direction;
        if(direction == "north" || direction == "west" || direction == "south" || direction == "east") 
        {
            Container* current = new Container;
            current = player->getCurrentContainer();
            player->move(direction, *gm);
            if(player->getCurrentContainer()->getName() == "empty")
            {
                player->setCurrentContainer(current);
                cout << "That's a dead end" << endl;
                cout << endl;
            } else if(player->getCurrentContainer()->getName() == "the Project Accelerator" )	   
            {
                cout << "You've gone in " << player->getCurrentContainer()->getName() << endl;
		cout << player->getCurrentContainer()->getDescription() << endl;
                cout << endl;
            } else
            {
		cout << "You've leaped to " <<player->getCurrentContainer()->getName() << endl;
		cout << player->getCurrentContainer()->getDescription() << endl;
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
        cout << "In " << player->getCurrentContainer()->getName() << endl;
        cout << "    " << player->getCurrentContainer()->getDescription() << endl;
        if(player->getCurrentContainer()->getItemsInContainer().empty())
        {
            cout << "There are no items in here " << endl;
            cout << endl;
        } else 
        {
            cout << "Items in this room: " << endl;
            for(unsigned int i = 0; i < player->getCurrentContainer()->getItemsInContainer().size(); i++)
            {
                cout << "- "<< player->getCurrentContainer()->getItemsInContainer().at(i)->getLongName() << endl;
            }
            cout << endl;
	} 
    } else if(command == "get") 
    {
        string object;
        cin >> object;
	    for(unsigned int i = 0; i < player->getCurrentContainer()->getItemsInContainer().size(); i++) 
            {
		if(player->getCurrentContainer()->getItemsInContainer().at(i)->getLongName() == object)
		{
                    cout << "You grabbed a " << object << endl;
                    player->pickup((*player).getCurrentContainer()->getItemsInContainer().at(i));
                    player->getCurrentContainer()->removeFromContainer(player->getCurrentContainer()->getItemsInContainer().at(i));
                    cout << endl;
                }
            }	
    } else if(command == "drop") 
    {
        string object;
        cin >> object;
        bool in = false;
        if(player->getItems()->getItemsInContainer().empty())
	{
            cout << "There is no " << object << " in your inventory" << endl;
            cout << endl;
        } else 
	  {
            for(unsigned int i = 0; i < player->getItems()->getItemsInContainer().size(); i++)
            {
                if(player->getItems()->getItemsInContainer().at(i)->getLongName() == object)
		{
                    cout << "You dropped a " << object << endl;
                    player->getCurrentContainer()->addToContainer(player->getItems()->getItemsInContainer().at(i));
                    player->getItems()->removeFromContainer(player->getItems()->getItemsInContainer().at(i));
                    cout << endl;
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
