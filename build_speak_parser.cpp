#include<iostream>
#include<sstream>
#include "database.h"
#include "common.h"
#include "game_server.h"
#include "build_speak_parser.h"
using namespace std;

void BuildParser::handleInput(Player *p, string command)
{	

    //command patterns
    regex createPattern1 ("create (.+) (.+) desc (.*)");
    regex connectPattern  ("connect room (.+) to (.+) via (.+)");
    regex putPattern  ("put item (.+) in room (.+)");
    regex setItemTypePattern ("set item (.+) (.+)");
    regex setStartingRoomPattern ("set room (.+) starting");
    regex setNotStartingRoomPattern("set room (.+) not starting");
    regex deleteRoomPattern("delete room (.+) (.+)");

    smatch m;
    
    if(command == "help"){
        server->printToUser(p,  "Room building commands: \n");
        server->printToUser(p,  "To create a room/item(will be unique by default) - create (room/item) <name> desc <description>");
        server->printToUser(p,  "To connect rooms - connect room <roomname> to <roomname> via (south, north, west, east)");
        server->printToUser(p,  "To put item - put item <itemname> in room <roomname>");
        server->printToUser(p,  "To set item type - set item <itemname> (unique, perplayer)");
        server->printToUser(p,  "To set starting room - set room <roomname> starting");
        server->printToUser(p,  "To set room not starting room- set room <roomname> not starting");
    }


    if(regex_match(command, m, setStartingRoomPattern)){
            string name = m[1];
            if(db->findRoomByName(name)){
                db->findRoomByName(name)->setStartingRoom(true);
                ostringstream os;
                os << "You set the starting room: " << name;
                server->printToUser(p, os.str());
            }else{
                server->printToUser(p, "Room not found!");
            }
     }


    if(regex_match(command, m, setNotStartingRoomPattern)){
            string name = m[1];
            if(db->findRoomByName(name)){
                db->findRoomByName(name)->setStartingRoom(false);
                ostringstream os;
                os << "You set the room: " << name << " not starting room";
                server->printToUser(p, os.str());
            }else{
                server->printToUser(p, "Room not found!");
            }
     }
    //Creation commands(items and rooms):
    //Format 1: create room/item called X and described by Y
    if (regex_match(command, m ,createPattern1)) {
        cout << "CREATING ROOM " << endl;
        string name = m[2];
        string description = m[3];
        if (p->getCanBuild()) {

            if (m[1] == "room") {
                if(db->findRoomByName(name) == NULL){

                    Room* tempR = new Room(name, description);
                    tempR->save();

                    ostringstream os1;
                    os1 << "You created a room: " << name;
                    server->printToUser (p, os1.str());

                    ostringstream os2;
                    os2 << "Description for this room: " << description;
                    server->printToUser (p, os2.str());
                }else{
                    server->printToUser(p, "Room already exists!");
                }
            }
            else if (m[1] == "item") {
                
                if(db->findItemByName(name) == NULL){
                    Item* tempI = new Item(name, description,p->getUsername(), UNIQUE);
                    tempI->save();

                    ostringstream os1, os2;
                    os1 << "You created an Item: " <<  name;
                    os2 <<  "Description for this item: " << description;

                    server->printToUser(p, os1.str());
                    server->printToUser(p, os2.str());
                }else{
                    server->printToUser(p, "Item already exists!");
                }
            }
        }
            else {
                server->printToUser(p, "You cannot build for now!");
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

        if(dir != "north" && dir != "south" && dir != "east" && dir != "west"){
            server->printToUser(p, "Please enter a valid direction(north, east, south, west)");
        }else{
            if(db->findRoomByName(room1) != NULL && db->findRoomByName(room2) != NULL){
                db->findRoomByName(room1)->setAdjacent(dir, db->findRoomByName(room2));
                ostringstream os;
                os <<"You connected room " <<  room1 <<  " and room " <<  room2 <<  " via " <<  dir;

                server->printToUser(p, os.str());

            }else{
                server->printToUser(p, "Room doesn't exist!");   
            }

        }
    }

    if(regex_match(command, m, setItemTypePattern)){
        string item = m[1];
        string type = m[2];
        ITEM_TYPE t;

        if(type == "unique"){
            t = UNIQUE;
        }else if(type == "perplayer"){
            t = PERPLAYER;
        }else{
            server->printToUser(p, "Please enter a valid item type(unique,perplayer)");
            return;
        }

        if(db->findItemByName(item) != NULL){
            if(db->findItemByName(item)->getType() == t){
                ostringstream os;
                os << "It's already "<< type << "!";
                server->printToUser(p, os.str());
            }else{
                db->findItemByName(item)->setType(t);
                ostringstream os;
                os << "You set the type: " << type;
                server->printToUser(p,os.str()); 
            } 
        }else{
            server->printToUser(p,"No such item!");
        }
    }
    if(regex_match(command, m, deleteRoomPattern)){
        string room = m[1];
        string roomName;
        if(db->findRoomByName(roomName) != NULL){
            db->deleteObject(db->findRoomByName(roomName)->getId()); 
        }
    }
}

