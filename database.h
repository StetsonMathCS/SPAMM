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
#include <vector>
class Item;
class Room;
class Player;

class Database{
    private:
        redisContext *context;
        vector<Item*> items;
        vector<Room*> rooms;
        vector<Player*> players;
    public:
        //values
        int lastid;
        Database(); //default constructor
        //methods
        void write(std::string, std::string);
        std::string read(std::string) const;
        Item * read_lastid_item(int);
        Room * read_lastid_room(int);
        Player * read_lastid_player(int);        
        void increment_lastid();
        Player * findPlayerByName(std::string);
        Item * findItemByName(std::string);
        Room * findRoomByName(std::string);
        vector<Player*> getPlayers();
};

#endif 
