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
    lastid=0;
    // TODO: load all items, players, and rooms into vectors
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
    string s(reply->str);
    freeReplyObject(reply);
    return s;
}

Item *Database::read_lastid_item(int id){
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

void Database::increment_lastid(){
    lastid++;
    write(to_string(-1),to_string(lastid));
}

Player* Database::findPlayerByName(string name) {
    for(int i = 0; i < players.size(); i++) {
        if(players[i]->getUsername() == name) {
            return players[i];
        }

        return NULL;
    }
}

Item* Database::findItemByName(string name) {
    for(int i = 0; i < items.size(); i++) {
        if(items[i]->getName() == name) {
            return items[i];
        }

        return NULL;
    }
}

Room* Database::findRoomByName(string name) {
    for(int i = 0; i < rooms.size(); i++) {
        if(rooms[i]->getTitle() == name) {
            return rooms[i];
        }
    }
    return NULL;
}

