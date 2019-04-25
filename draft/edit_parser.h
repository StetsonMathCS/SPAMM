#ifndef EDIT_PARSER_H
#define EDIT_PARSER_H


#include <string>
#include <map>
#include <utility>

#include "player.h"
#include "room.h"

class GameServer;

class EditParser {
    
    public:
        
        static void handleeditInput(GameServer*, int, std::string);

};

#endif
