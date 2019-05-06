#include "database.h"
#include "common.h"
#include <string>
#include <iostream>
#include <sstream>
#include "item.h"
#include "room.h"
#include "player.h"
using namespace std;

Database::Database(){ 
    context = redisConnect("localhost",6379); 
    string lastid_str = read("lastid");
    if(lastid_str == "")
        lastid = -1;
    else
        lastid = stoi(lastid_str);
    cout << "DB lastid = " << lastid << endl;
    // TODO: load all items, players, and rooms into vectors
    for(int i = 0; i <= lastid; ++i) {
        string dataFromRedis = read(to_string(i));
        //cout << "At index " << i << endl;
        //If the first part of the string is player, then the object stored at that index is a player, parse and load a player
        if(dataFromRedis.substr(0,6) == "player") {
            players.push_back(read_lastid_player(i));
        } else if(dataFromRedis.substr(0,4) == "item"){
            items.push_back(read_lastid_item(i));          
        } else if(dataFromRedis.substr(0,4) == "room"){
            rooms.push_back(read_lastid_room(i));
        } else {
            //There should never be anything in the database that can't be parsed, if this is printed there is an error
            cout << "ERROR: COULD NOT PARSE DATABASE ENTRY AT ID " << i << endl;
        }
        
    }
} 

//Sets/writes a value to an assigned KEY using redisContext
void Database::write(string key, string value){
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}

//Gets/reads value of an assigned KEY using redisContext
string Database::read(string key) const{
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"GET %s", key.c_str());
    if(reply->type == 4) {
        return "";
        freeReplyObject(reply);
    }
    string s(reply->str);
    freeReplyObject(reply);
    return s;
}

Item * Database::read_lastid_item(int id){
    Item *i = new Item("","","",UNIQUE);
    string temp = read(to_string(id));
    istringstream data(temp);
    string name;
    string desc;
    string type;
    string owner;
    string line;
    //The first line is just item, so it isn't needed
    getline(data,line);
    //The name of the object
    getline(data,line);
    name = line.substr(6);
    i->setName(name);
    //Description of the object
    getline(data,line);
    desc = line.substr(5);
    i->setDesc(desc);
    getline(data,line);
    owner = line.substr(6);
    i->setOwner(owner);
    getline(data,line);
    type = line;
    //The type of the item is either PERPLAYER or UNIQUE.
    if(line=="PERLAYER"){
        i->setType((ITEM_TYPE)0);
    }else{
        i->setType((ITEM_TYPE)1);
    }
    return i;
} 

Room * Database::read_lastid_room(int id){
    Room * r = new Room("","");
    string temp = read(to_string(id));
    istringstream data(temp);
    string title;
    string desc;
    string line;

    //The first line is just "room" disregard the line
    getline(data,line);

    //Line with the title of the room
    getline(data,line);
    title = line.substr(7);
    r->setTitle(title);
   
    //Line with the description of the room
    getline(data,line);
    desc = line.substr(5);
    r->setDesc(desc); 
    
   return r;
}

Player * Database::read_lastid_player(int id){
    Player * p = new Player("","",-1);
    string temp = read(to_string(id));
    istringstream data(temp);
    string username;
    string description;
    string password;
    string line;

    //The first line in the database is the description that they are a player, ignore the first line
    getline(data,line);
    //Now the username is stored in the variable line
    getline(data,line);
    username = line.substr(10);
    p->setUsername(username);
    
    getline(data,line);
    description = line.substr(5);
    p->setDescription(description);
    p->setID(id);
    getline(data,line);
    password = line;
    p->setPassword(password);

    return p;
}

void Database::increment_lastid(){
    lastid++;
    write("lastid",to_string(lastid));
}

void Database::clearDatabase(){
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"FLUSHALL");
    freeReplyObject(reply);

}

void Database::addPlayer(Player *p) {
    // possibly replace known player by this id
    for(unsigned int i = 0; i < players.size(); i++) {
        if(players[i]->getID() == p->getID()) {
            players[i] = p;
            return;
        }
    }
    players.push_back(p);
}

Player* Database::findPlayerById(int id) {
    for(unsigned int i = 0; i < players.size(); i++) {
        if(players[i]->getID() == id) {
            return players[i];
        }
    }
    return NULL;
}

Player* Database::findPlayerByName(string name) {
    for(unsigned int i = 0; i < players.size(); i++) {
        if(players[i]->getUsername() == name) {
            return players[i];
        }
    }
    return NULL;
}

void Database::addItem(Item *it) {
    // possibly replace known item by this name
    for(unsigned int i = 0; i < items.size(); i++) {
        if(items[i]->getName() == it->getName()) {
            items[i] = it;
            return;
        }
    }
    items.push_back(it);
}

Item* Database::findItemByName(string name) {
    for(unsigned int i = 0; i < items.size(); i++) {
        if(items[i]->getName() == name) {
            return items[i];
        }
    }
    return NULL;
}

void Database::addRoom(Room *r) {
    // possibly replace known room by this title
    for(unsigned int i = 0; i < rooms.size(); i++) {
        if(rooms[i]->getTitle() == r->getTitle()) {
            rooms[i] = r;
            return;
        }
    }
    rooms.push_back(r);
}

Room* Database::findRoomByName(string name) {
    for(unsigned int i = 0; i < rooms.size(); i++) {
        if(rooms[i]->getTitle() == name) {
            return rooms[i];
        }
    }
    return NULL;
}

vector<Player*> Database::getPlayers() {
    return players;
}
