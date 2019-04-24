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
        //values
        int lastid=0;
        Database(){ context = redisConnect("localhost",6379); } //default constructor
        //methods
        void write(std::string key, std::string value){
            redisReply *reply;
            reply = (redisReply*) redisCommand(context,"SET %s %s", key.c_str(), value.c_str());
            freeReplyObject(reply);
        }
        std::string read(std::string key) const{
            redisReply *reply;
            reply = (redisReply*) redisCommand(context,"GET %s", key.c_str());
            std::string s(reply->str);
            std::cout << s;
            freeReplyObject(reply);
            return s;

        }
        void read_lastid(int id) const;
        void increment_lastid();
};

#endif 
