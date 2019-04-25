#ifndef BUILD_SPEAK_PARSER
#define BUILD_SPEAK_PARSER
#include<regex>
#include "item.h"
#include "room.h"
#include "player.h"

class GameServer;
class Build_speak_parser {
	public:
//		Build_speak_parser(Player*);
		static void handleInput(GameServer*, int, std::string);



};
#endif 
