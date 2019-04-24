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
        void write(std::string key, std::string value); 
        std::string read(std::string key) const;
        void read_lastid(int id) const;
        void increment_lastid();
};

#endif 
