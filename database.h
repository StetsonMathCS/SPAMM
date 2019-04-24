/**
 *Database class that uses Hiredis library. It conceals the more technical aspects about the Hiredis library.
 *
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include <string>
#include <iostream>
#include "hiredis.h"
class Database{
    private:
        redisContext *context;

    public:
        Database(){ context = redisConnect("localhost",6379); } //default constructor
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
        int lastid;
        void read_lastid(int id);

};

#endif 
