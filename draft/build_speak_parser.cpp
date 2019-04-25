#include<iostream>
#include<sstream>
#include "build_speak_parser.h"
using namespace std;


/*
Pass in a command to realize(Only print for now).
*/
void Build_speak_parser::handleInput(GameServer* server, int id, string command)
{	
    createPattern1 = ("create (.+) called (.+) and described by (.*)");
    createPattern2 = ("create (.+) (.+)");
    connectPattern = ("connect room (.+) to (.+) via (.+)");
    sayPattern = ("say (.*)");
    tellPattern = ("tell user (.+): (.*)");
    putPattern = ("put item (.+) in room (.+)");

   
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
            ostringstream os1;
            os1 << "You created a room: " << name;
            server->printToUser (id, os1.str());

            ostringstream os2;
            os2 << "Description for this room: " << description;
            server->printToUser (is, os2.str());
        }
        else if (m[1] == "item") {

            tempItem = new Item(name, description);
            //TODO: Put item in player's inventory. 
            //		When reaching the limit, drop item to the player's room.
            if (myPlayer->getCanBuild() != false) {
                myPlayer->addItemToInventory(tempItem);
                ostringstream os1, os2;
                os1 << "You created an Item: " <<  name;
                os2 <<  "Description for this item: " << description;

                server->printToUser(id, os1.str());
                server->printToUser(id, os2,str());
            }
            else {
                server->printToUser(id, "Your bag is full!");
            }
        }

    }
    /*
    else if (regex_match(input, m, createPattern2)) {
        string name = m[2];
        string description;

        if (m[1] == "room") {
            server->printToUser   "You are going to creat a room: "   name   endl;
            server->printToUser   "Please describe it: "   endl;
            server->printToUser   "> ";
            getline(cin, description);

            //TODO: create a room
            tempRoom = new Room(name, description);


            server->printToUser   "You created a room: "   name   endl;
            server->printToUser   "Description: "   description   endl;
            return true;
        }
        else if (m[1] == "item") {
            server->printToUser   "You are going to creat an item: "   name   endl;
            server->printToUser   "Please describe it: "   endl;
            server->printToUser   "> " ;
            getline(cin, description);

            //TODO: Put item in player's inventory. 
            //		When reaching the limit, drop item to the player's room.
            tempItem = new Item(name, description);
            if (myPlayer->getCanBuild() != false) {
                myPlayer->addItemToInventory(tempItem);
                server->printToUser   "You created an Item: "   name   endl;
                server->printToUser   "Description for this item: "   description   endl;
                server->printToUser   "Item added to player: "   myPlayer->getUsername()   endl;
            }
            else {
                myPlayer->getRoom()->addItemToFloor(tempItem);
                server->printToUser   "Your bag is full! Item will be droped to the floor."   endl;
                server->printToUser   "You created an Item: "   name   endl;
                server->printToUser   "Description for this item: "   description   endl;
            }
            return true;
        }
    }*/

    //Put item command
    //Format: put item X in room Y
    if (regex_match(input, m, putPattern)) {

        string item = m[1];
        string room = m[2];

        //TODO: Put the item into the room
        ostringstream os;
        os << "You put item " <<  item <<  " into room " <<  room; 

        server->printToUser(id, os.str());
    }

    //Connect command
    //Format: connect room X to Y via DIR
    if (regex_match(input, m, connectPattern)) {

        string room1 = m[1];
        string room2 = m[2];
        string Dir = m[3];

        //TODO: connect the rooms
        
        ostringstream os;
        os <<"You connected room " <<  room1 <<  " and room " <<  room2 <<  " via " <<  dir;

        server->printToUser(id, os.str());
    }

    //Say command
    //Format: say X
    if (regex_match(input, m, sayPattern)) {

        string message = m[1];

        //TODO: Display the message
        ostringstream os;
        os<<  "Player: " << id << " said: " <<  message; 
        server->printToUser(id, os.str());
    }

    //tell command
    //Format: tell user NAME: XYZ
    if (regex_match(input, m, tellPattern)) {
        string user = m[1];
        string messages = m[2];

        //TODO: Display the message to sent user
        ostringstream os1,os2;
        os1<< "Player: "<< id << " sent a message to " << m[1] << ": "; 

        server->printToUser(id, os1.str());
        server->printToUser(id, messages);
    }
}

