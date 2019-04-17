://github.com/StetsonMathCS/SPAMMinclude <stdio.h>
#include <stdlib.h>
#include "hiredis.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

//Sets/writes VALUE to an assigned KEY using redisContext c
//These two methods make it easy and seamless to transfer data. Put another way, others shouldn't
//have to construct reply information and free it.
void write(redisContext *c, string const &key, string const &value){
    redisReply *reply;
    reply = (redisReply*) redisCommand(c,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}

//Gets/reads value of an assigned KEY using redisContext c
string read(redisContext *c, string const &key){
    redisReply *reply;
    reply = (redisReply*) redisCommand(c,"GET %s", key.c_str());
    string s(reply->str);
    cout << s;
    freeReplyObject(reply);
    return s;
}

int main (){
    redisContext *c = redisConnect("localhost",6379);
    //This port is probably not correct but I put one in so it would work

    //establish connection
    

    if (c!=NULL && c->err){
        cout << "Error...Connection Failed!" << endl; 
        assert(c!=NULL && c->err);
    }else{
        cout << "Connected." << endl;
    }

    string roomG = "ROOM G";
    string value = "information";
    write(c, "ROOM G", "ROOM G INFO");
    read(c, "ROOM G");

    
    return 0;
}
