#include "game_server.h"
#include "action_parser.h"
#include "player.h"
#include "build_speak_parser.h"
#include "common.h"
#include "database.h"
#include<iostream>

GameServer *server;
Database *db;

using namespace std;

//Functions that will be called when user enters information
int logOnFunction(string,string);
int newUserFunction(string,string);

void parseInput(int playerId, string input) {
    ActionParser::handleInput(server, playerId, input);
    BuildParser::handleInput(server, playerId, input);
}

int main() {
    db = new Database();
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
    server->setCreateNewUserFunction(newUserFunction);

	//Start the server
	server->start();
	
    delete db;
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

int newUserFunction(string username, string password) {
    //If the username is already taken then return -1 to indicate that there wasn't a new account created, else return a userId for the new user
    
    //Example that a username has been taken
    if(username == "alreadyTaken")
        return -1;
    else
        return 100;

}
