#ifndef PARSER_H
#define PARSER_H

#include "gamemap.h"
#include "player.h"
#include "container.h"

class Parser {
    public:
        bool handleInput(Player*, GameMap*);
};

#endif
