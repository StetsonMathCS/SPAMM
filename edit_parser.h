#ifndef EDIT_PARSER_H
#define EDIT_PARSER_H


#include <string>
#include <map>
#include <utility>
#include <regex>

#include "player.h"
#include "room.h"
#include "item.h"

class EditParser {
    
    public:
        
        static void handleeditInput(Player*, std::string);

};

#endif
