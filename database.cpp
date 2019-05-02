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
            string name, desc;
            //WARNING -- If the way a player is stored gets change, this code will break
            string descMarker = "\ndesc:";
            
            //The first char of the username is at index 18
            //The last character is right before the "\ndesc:" part
            name = dataFromRedis.substr(18, dataFromRedis.find(descMarker) - 18);
            //cout << "LOADING DATA AND FOUND THIS NAME " << name << endl;
            //The description is from the end of "\ndesc:" to 2 from the end of the string
            desc = dataFromRedis.substr(dataFromRedis.find(descMarker) + descMarker.length());
            desc = desc.substr(0, desc.length() - 1);
            //cout << "LOADING THIS AS DESC " << desc << endl;
            Player *tempPlayer = new Player(name, desc, i);
            players.push_back(tempPlayer);
        }

        if(dataFromRedis.substr(0,4) == "item"){
            items.push_back(read_lastid_item(lastid));          
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
    getline(data,line);
    name = line;
    cout << name << endl;
    i->setName(name);
    getline(data,line);
    desc = line;
    cout << desc << endl;
    i->setDesc(desc);
    getline(data,line);
    owner = line;
    cout << owner << endl;
    i->setOwner(owner);
    getline(data,line);
    type = line;
    if(line=="PERLAYER"){
        i->setType((ITEM_TYPE)1);
    }else{
        i->setType((ITEM_TYPE)2);
    }
    cout << line << endl;
    i->setType(PERPLAYER);
    return i;
} 

Room * Database::read_lastid_room(int id){
    Room * r = new Room("","");
    string temp = read(to_string(id));
    istringstream data(temp);
    string title;
    string desc;
    string line;

    getline(data,line);
    title = line;
    cout << title << endl;
    r->setTitle(title);
   
    getline(data,line);
    desc = line;
    cout << desc << endl;
    r->setDesc(title,desc); 
    
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

    getline(data,line);
    username = line;
    cout << username << endl;
    p->setUsername(username);
    
    getline(data,line);
    description = line;
    cout << description << endl;
    p->setDescription(description);

    getline(data,line);
    password = line;
    p->setPassword(password);

    return p;
}

void Database::increment_lastid(){
    lastid++;
    write("lastid",to_string(lastid));
}

Player* Database::findPlayerByName(string name) {
    for(int i = 0; i < players.size(); i++) {
        if(players[i]->getUsername() == name) {
            return players[i];
        }
    }
    return NULL;
}

Item* Database::findItemByName(string name) {
    for(int i = 0; i < items.size(); i++) {
        if(items[i]->getName() == name) {
            return items[i];
        }
    }
    return NULL;
}

Room* Database::findRoomByName(string name) {
    for(int i = 0; i < rooms.size(); i++) {
        if(rooms[i]->getTitle() == name) {
            return rooms[i];
        }
    }
    return NULL;
}

vector<Player*> Database::getPlayers() {
    return players;
}
