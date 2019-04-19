#include<iostream>
#include "build_speak_parser.h"
using namespace std;

Build_speak_parser::Build_speak_parser()
{
//	myPlayer = p;
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


				cout << "You created a room: " << name << endl;
				cout << "Describtion for this room: " << description << endl;
				return true;
			}
			else if (m[1] == "item") {

				//TODO: Create an item


				cout << "You created an Item: " << name << endl;
				cout << "Describtion for this item: " << description << endl;
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


				cout << "You created a room: " << name << endl;
				cout << "Description: " << description << endl;
				return true;
			}
			else if (m[1] == "item") {
				cout << "You are going to creat an item: " << name << endl;
				cout << "Please describe it: " << endl;
				cout << "> " ;
				getline(cin, description);

				//TODO: create an item


				cout << "You created an item: " << name << endl;
				cout << "Description: " << description << endl;
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

			cout << "User_name said: " << message << endl;
			return true;
		}

		//tell command
		//Format: tell user NAME: XYZ
		if (regex_match(input, m, tellPattern)) {
			string user = m[1];
			string messages = m[2];

			//TODO: Display the message to sent user

			cout << "User_name sent a message to "<<m[1]<<": " << endl;
			cout << messages << endl;
			return true;
		}
		return false;
}

/*
Simple execution example
*/
int main()
{
	Build_speak_parser * test = new Build_speak_parser();
	string input;
	while (true) {
		cout << "> ";
		getline(cin, input);
		if (input == "quit") break;
		if (test->activities(input) == false) {
			cout << "Type a vaild input!" << endl;
		}
	}

	delete test;

}


