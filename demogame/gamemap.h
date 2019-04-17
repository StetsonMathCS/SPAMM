#ifndef GAMEMAP_H
#define GAMEMAP_H

#include "container.h"

#include <map>
#include <utility>
#include <string>

class GameMap {
    private:
        std::map<Container*, std::map<std::string, Container*> > exits;

    public:
        void setAdjacent(Container* r1, Container* r2, std::string dir) {
           exits[r1][dir] = r2;
        }
        std::map<Container*, std::map<std::string, Container*> > getGameMap(){
            return exits;
        }
};

#endif
