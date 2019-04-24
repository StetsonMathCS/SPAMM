#include "redisdemo.h"
#include <string>
#include <iostream>
using namespace std;

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

//This looks like it does nothing now, but it should interact with item ids.
void read_lastid(int id) const{
    read(toString(id));
} 

void increment_lastid(){
    lastid++; 
}
