#ifndef BUILD_SPEAK_PARSER
#define BUILD_SPEAK_PARSER
#include<regex>
#include "item.h"
#include "room.h"
#include "player.h"

class BuildParser {
	public:
		static void handleInput(Player*, std::string);
};
#endif 
