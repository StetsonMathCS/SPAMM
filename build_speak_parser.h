#ifndef BUILD_SPEAK_PARSER
#define BUILD_SPEAK_PARSER
#include<regex>
#include "item.h"
#include "room.h"
#include "player.h"

class Build_speak_parser {
	public:
		Build_speak_parser(Player*);
		bool activities(string);


	private:
		string input;
		Player * myPlayer;
		Room *tempRoom;
		Item *tempItem;
		regex sayPattern;
		regex tellPattern;
		regex createPattern1;
		regex createPattern2;
		regex connectPattern;
		regex putPattern;


};
#endif 
