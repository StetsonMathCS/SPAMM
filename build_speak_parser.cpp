#include<iostream>
#include<sstream>
#include "database.h"
#include "common.h"
#include "game_server.h"
#include "build_speak_parser.h"
using namespace std;


/*
Pass in a command to realize(Only print for now).
*/
void BuildParser::handleInput(Player *p, string command)
{	

    //command patterns
    regex createPattern1 ("create (.+) called (.+) and described by (.*)");
    //regex createPattern2 ("create (.+) (.+)");
    regex connectPattern  ("connect room (.+) to (.+) via (.+)");
    //regex sayPattern  ("say (.*)");
    //regex tellPattern  ("tell user (.+): (.*)");
    regex putPattern  ("put item (.+) in room (.+)");

    smatch m;
    

    //Creation commands(items and rooms):
    //Format 1: create room/item called X and described by Y
    //Format 2: create room/item X (describtion will be typed later)
    if (regex_match(command, m ,createPattern1)) {

        string name = m[2];
        string description = m[3];

        if (m[1] == "room") {

             
            Room* tempR = new Room(name, description);
            //tempR->save();

            ostringstream os1;
            os1 << "You created a room: " << name;
            server->printToUser (p, os1.str());

            ostringstream os2;
            os2 << "Description for this room: " << description;
            server->printToUser (p, os2.str());
        }
        else if (m[1] == "item") {

            //TODO: Put item in player's inventory. 
            //		When reaching the limit, drop item to the player's room.
           
           //Build condition should be check before creating
           //Need findPlayerById Funtion
            if (true) {
                //Need Owner
                //Item* tempI = new Item(name, description);
                //tempI.save();

                ostringstream os1, os2;
                os1 << "You created an Item: " <<  name;
                os2 <<  "Description for this item: " << description;

                server->printToUser(p, os1.str());
                server->printToUser(p, os2.str());
            }
            else {
                server->printToUser(p, "Your bag is full!");
            }
        }

    }
   

    //Put item command
    //Format: put item X in room Y
    if (regex_match(command, m, putPattern)) {

        string item = m[1];
        string room = m[2];

        //Add item to room and print
        if(db->findItemByName(item) != NULL && db->findRoomByName(room) != NULL){
            db->findRoomByName(room)->addItemToFloor(db->findItemByName(item));
            ostringstream os;
            os << "You put item " <<  item <<  " into room " <<  room; 
            server->printToUser(p, os.str());

        }else{
            server->printToUser(p, "There is no such item or room");
        }
    }

    //Connect command
    //Format: connect room X to Y via DIR
    if (regex_match(command, m, connectPattern)) {

        string room1 = m[1];
        string room2 = m[2];
        string dir = m[3];
        
        if(dir != "north" || dir != "south" || dir != "east" || dir != "west"){
            server->printToUser(p, "Please enter a valid direction(north, east, south, west)");
        }else{
            if(db->findRoomByName(room1) != NULL && db->findRoomByName(room2) != NULL){
                db->findRoomByName(room1)->setAdjacent(dir, db->findRoomByName(room2));
                ostringstream os;
                os <<"You connected room " <<  room1 <<  " and room " <<  room2 <<  " via " <<  dir;

                server->printToUser(p, os.str());

            }else{
                server->printToUser(p, "Room doesn't exit!");   
            }

        }
    }
    
    /*
    //Say command
    //Format: say X
    if (regex_match(command, m, sayPattern)) {

        string message = m[1];

        //TODO: Display the message
        ostringstream os;
        os<<  "Player: " << id << " said: " <<  message; 
        server->printToUser(p, os.str());
    }

    //tell command
    //Format: tell user NAME: XYZ
    if (regex_match(command, m, tellPattern)) {
        string user = m[1];
        string messages = m[2];

        //TODO: Display the message to sent user
        ostringstream os1,os2;
        os1<< "Player: "<< id << " sent a message to " << m[1] << ": "; 

        server->printToUser(p, os1.str());
        server->printToUser(p, messages);
    }

    */
}

