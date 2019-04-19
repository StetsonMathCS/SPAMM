/*
 *
 * redisdemo.cpp
 *
 *  Created on: Apr 18, 2019
 *      Author: SMING
 */
#include "redisdemo.h"
#include <string>
#include <iostream>
using namespace std;
void RedisDemo::write(string key, string value){
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"SET %s %s", key.c_str(), value.c_str());
    freeReplyObject(reply);
}

//Gets/reads value of an assigned KEY using redisContext c
string RedisDemo::read(string key){
    redisReply *reply;
    reply = (redisReply*) redisCommand(context,"GET %s", key.c_str());
    string s(reply->str);
    cout << s;
    freeReplyObject(reply);
    return s;
}


