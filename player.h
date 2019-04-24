#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <set>
#include "item.h"
#include "room.h"

class Item;
class Room;

class Player {
    private:
        Room *room;
        std::string username;
        std::string password;
        std::string description;
	std::string id;
        std::string lastLoginIp;
        std::string lastLoginTime;
        std::set<Item*> inventory; 
        bool canBuild;
    public:
        Player();
        Player(std::string, std::string, int);
        void setRoom(Room*);
        Room* getRoom() const;
        void listInventory() const;
        void addItemToInventory(Item*);
        Item* findItemInInventory(std::string) const;
        void setCanBuild(bool);
        bool getCanBuild() const;
        void setUsername(std::string);
        std::string getUsername() const;
        void setLastLoginIp(std::string);
        std::string getLastLoginIp() const;
        void setLastLoginTime(std::string);
        std::string getLastLoginTime() const;
        void setPassword(std::string);
        std::string getPassword() const;
        void setDescription(std::string);
        std::string getDescription() const;
	void setID(int);
	int getID() const;
	//bool connected() const;
};

#endif

