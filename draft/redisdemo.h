/*
 * redisdemo.h
 *
 *  Created on: Apr 18, 2019
 *      Author: SMING
 */


#ifndef REDISDEMO_H_
#define REDISDEMO_H_
#include <string>
#include <iostream>
#include "hiredis.h"
	class RedisDemo{
	public:
		RedisDemo(){ context = redisConnect("localhost",6379); }
		void write(std::string key, std::string value){
             redisReply *reply;
             reply = (redisReply*) redisCommand(context,"SET %s %s", key.c_str(), value.c_str());
             freeReplyObject(reply);
        }
        std::string read(std::string key){
            redisReply *reply;
            reply = (redisReply*) redisCommand(context,"GET %s", key.c_str());
            std::string s(reply->str);
            std::cout << s;
            freeReplyObject(reply);
            return s;

        }
		redisContext *context;
	};




#endif /* REDISDEMO_H_ */
