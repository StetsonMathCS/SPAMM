#include<iostream>
#include "build_speak_parser.h"
using namespace std;

Build_speak_parser::Build_speak_parser(Player* p)
{
	myPlayer = p;
	createPattern1 = ("create (.+) called (.+) and described by (.*)");
	createPattern2 = ("create (.+) (.+)");
	connectPattern = ("connect room (.+) to (.+) via (.+)");
	sayPattern = ("say (.*)");
	tellPattern = ("tell user (.+): (.*)");
	putPattern = ("put item (.+) in room (.+)");
}

/*
Pass in a command to realize(Only print for now).
*/
bool Build_speak_parser::activities(string command)
{
		input = command;
		smatch m;

		//Creation commands(items and rooms):
		//Format 1: create room/item called X and described by Y
		//Format 2: create room/item X (describtion will be typed later)
		if (regex_match(input, m ,createPattern1)) {

			string name = m[2];
			string description = m[3];

			if (m[1] == "room") {

				// TODO: Create a room 
				tempRoom = new Room(name, description);


				cout << "You created a room: " << name << endl;
				cout << "Description for this room: " << description << endl;
				return true;
			}
			else if (m[1] == "item") {

				tempItem = new Item(name, description);
				//TODO: Put item in player's inventory. 
				//		When reaching the limit, drop item to the player's room.
				if (myPlayer->getCanBuild() != false) {
					myPlayer->addItemToInventory(tempItem);
					cout << "You created an Item: " << name << endl;
					cout << "Description for this item: " << description << endl;
					cout << "Item added to player: " << myPlayer->getUsername() << endl;
				}
				else {
					myPlayer->getRoom()->addItemToFloor(tempItem);
					cout << "Your bag is full! Item will be droped to the floor." << endl;
					cout << "You created an Item: " << name << endl;
					cout << "Description for this item: " << description << endl;
				}
				return true;
			}

		}
		else if (regex_match(input, m, createPattern2)) {
			string name = m[2];
			string description;

			if (m[1] == "room") {
				cout << "You are going to creat a room: " << name << endl;
				cout << "Please describe it: " << endl;
				cout << "> ";
				getline(cin, description);

				//TODO: create a room
				tempRoom = new Room(name, description);


				cout << "You created a room: " << name << endl;
				cout << "Description: " << description << endl;
				return true;
			}
			else if (m[1] == "item") {
				cout << "You are going to creat an item: " << name << endl;
				cout << "Please describe it: " << endl;
				cout << "> " ;
				getline(cin, description);

				//TODO: Put item in player's inventory. 
				//		When reaching the limit, drop item to the player's room.
				tempItem = new Item(name, description);
				if (myPlayer->getCanBuild() != false) {
					myPlayer->addItemToInventory(tempItem);
					cout << "You created an Item: " << name << endl;
					cout << "Description for this item: " << description << endl;
					cout << "Item added to player: " << myPlayer->getUsername() << endl;
				}
				else {
					myPlayer->getRoom()->addItemToFloor(tempItem);
					cout << "Your bag is full! Item will be droped to the floor." << endl;
					cout << "You created an Item: " << name << endl;
					cout << "Description for this item: " << description << endl;
				}
				return true;
			}
		}

		//Put item command
		//Format: put item X in room Y
		if (regex_match(input, m, putPattern)) {

			string item = m[1];
			string room = m[2];

			//TODO: Put the item into the room


			cout << "You put item " << item << " into room " << room << endl;
			return true;
		}

		//Connect command
		//Format: connect room X to Y via DIR
		if (regex_match(input, m, connectPattern)) {

			string room1 = m[1];
			string room2 = m[2];
			string DIR = m[3];

			//TODO: connect the rooms

			cout << "You connected room " << room1 << " and room " << room2 << " via " << DIR << endl;
			return true;
		}

		//Say command
		//Format: say X
		if (regex_match(input, m, sayPattern)) {

			string message = m[1];

			//TODO: Display the message

			cout << myPlayer->getUsername() <<" said: " << message << endl;
			return true;
		}

		//tell command
		//Format: tell user NAME: XYZ
		if (regex_match(input, m, tellPattern)) {
			string user = m[1];
			string messages = m[2];

			//TODO: Display the message to sent user

			cout <<myPlayer->getUsername() <<" sent a message to "<<m[1]<<": " << endl;
			cout << messages << endl;
			return true;
		}
		return false;
}

