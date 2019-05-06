#ifndef ACTION_PARSER_H

#define ACTION_PARSER_H


#include <string>
#include "player.h"

#include "room.h"

class ActionParser {

    public:

        static bool handleInput(Player*, std::string);

};

#endif
