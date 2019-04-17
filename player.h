#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Room;

class Player {
    private:
        Room *room;
        std::string username;
        std::string password;
        std::string description;
        std::string playerId;
        bool canBuild;
    public:
        Player();
        void setRoom(Room*);
        Room* getRoom();
        void listInventory() const;
        bool getCanBuild();
        void setUsername(std::string);
        void setPlayerId(std::string);
        void setPassword(std::string);
        void setDescription(std::string);
};

#endif
