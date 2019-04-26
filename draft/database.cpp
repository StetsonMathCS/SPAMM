#include "database.h"
#include <string>
#include <iostream>
#include <sstream>
#include "item.h"
using namespace std;

Database::Database(){ 
    context = redisConnect("localhost",6379); 
    lastid=0;
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

Item *Database::read_lastid(int id){
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
