/*
 *
 * redisdemo.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: SMING
 */
#include "hiredis.h"
#include "redisdemo.h"
#include <string>
using namespace std;

redisdemo::redisdemo(){
	context = redisConnect("localhost",6379);

}


void redisdemo::write(redisContext *c, string const &key, string const &value){
    redisReply *reply;
    reply = (redisReply*) redisCommand(c,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}

//Gets/reads value of an assigned KEY using redisContext c
string redisdemo::read(redisContext *c, string const &key){
    redisReply *reply;
    reply = (redisReply*) redisCommand(c,"GET %s", key.c_str());
    string s(reply->str);
    cout << s;
    freeReplyObject(reply);
    return s;
}


