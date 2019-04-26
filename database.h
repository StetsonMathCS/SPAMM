/**
 *Database class that uses Hiredis library. It conceals the more technical aspects about the Hiredis library.
 *-Stephen Mingolelli
 *-Nicola Mingolelli
 */

#ifndef DATABASE_H_
#define DATABASE_H_
#include <string>
#include "item.h"
#include <iostream>
#include "hiredis.h"
class Item;
class Database{
    private:
        redisContext *context;
    public:
        //values
        int lastid;
        Database(); //default constructor
        //methods
        void write(std::string, std::string);
        std::string read(std::string) const;
        Item *read_lastid(int);
        void increment_lastid();
};

#endif 
