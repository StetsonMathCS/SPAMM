#ifndef SPEAK_PARSER_H
#define SPEAK_PARSER_H

#include <string>
#include <map>
#include <utility>
#include <regex>

#include "player.h"
#include "room.h"
#include "item.h"

class SpeechParser {

    public:
    
        static void handlespeechInput(Player*, std::string);
};

#endif
