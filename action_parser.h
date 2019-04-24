#ifndef ACTION_PARSER_H

#define ACTION_PARSER_H


#include <string>
#include "player.h"

#include "room.h"

class GameServer;

class ActionParser {

    public:

        static void handleInput(GameServer*, int, std::string);

};

#endif
