#ifndef PLAYER_H
#define PLAYER_H

#include "container.h"
#include "gamemap.h"

using namespace std;

class Player : public Item{
    private:
        Container* currentContainer;
        Container* items = new Container;
    public:
	void setCurrentContainer(Container*);
        Container* getCurrentContainer();
        Container* getItems();
        void pickup(Item*);
        void move(std::string&, GameMap&);
};

#endif

