#ifndef PLAYER_H
#define PLAYER_H

class Room;

class Player {
    private:
        Room *room;
    public:
        Player();
        void setRoom(Room*);
        Room* getRoom();
        void listInventory() const;
};

#endif
