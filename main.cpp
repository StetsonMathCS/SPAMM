#include "game_server.h"
#include "action_parser.h"
#include "player.h"
#include "build_speak_parser.h"
#include<iostream>

using namespace std;

//Functions that will be called when user enters information
int logOnFunction(string,string);

//Global Refrence so the two functions can refrence it
GameServer *server;

void parseInput(int playerId, string input) {
    ActionParser::handleInput(server, playerId, input);
    BuildParser::handleInput(server, playerId, input);
}

int main() {
    // TODO: REMOVE
    //
    Player *p1 = new Player;
    Player *p2 = new Player;
    //parser.handleInput(p1);
    delete p1;
    


	
	//Instantiate a Game server on the defualt port 2323
	server = new GameServer();
	//Instantiate a Game server on a specific port 
	//IT NEEDS TO BE ABOVE 1024 to not require root permissions
	//server = new GameServer(2323);
    
    
	//When a user enters their credentials, they are checked with this function, the function returns a unique id
	server->setLogOnFunction(logOnFunction);
	//When a user enters a line, this function is called to handle the parsing and response generation
	server->setCallBackFunction(parseInput);

	//Start the server
	server->start();
	
return 0;
}

int logOnFunction(string username, string password) {
	bool isCorrect = (username == "Username" && password == "Password");

	if(isCorrect)
		//Example userID
		return 100;
	else
		return -1;
}	
