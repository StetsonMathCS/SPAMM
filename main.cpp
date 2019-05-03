#include "game_server.h"
#include "action_parser.h"
#include "edit_parser.h"
#include "speak_parser.h"
#include "player.h"
#include "build_speak_parser.h"
#include "common.h"
#include "database.h"
#include "player.h"
#include <iostream>
#include <csignal>

GameServer *server;
Database *db;

using namespace std;

//Functions that will be called when user enters information
Player* logOnFunction(string,string);
int newUserFunction(string,string);

//Signal handling
void exitHandler(int);

//Default starting room
Room *startingRoom;
void parseInput(Player *p, string input) {
	ActionParser::handleInput(p, input);
	BuildParser::handleInput(p, input);
	EditParser::handleeditInput(p, input);
    SpeechParser::handlespeechInput(p, input);
}

int main() {
    //Default starting room
    startingRoom = new Room("LRoom", "Living room with a nice couch");
    Room *adjacent = new Room("Dining Room", "Large table and plenty of chairs");
    startingRoom->setAdjacent("East", adjacent);
    //
	db = new Database();
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
	//Register signal handling
	signal(SIGINT, exitHandler);

	//Start the server
	server->start();
	delete db;
	return 0;
}

void exitHandler(int signal) {
	cout << "\n Exiting..." << endl;
	//Close connections and free memory

	//exit sucessfully
	exit(0);
}
Player* logOnFunction(string username, string password) {
    //The database stores a list of players in memory
    //This functions loops through them and comapres the username and "desrcriptions" (passwords) of them

        Player *possibleUser = db->findPlayerByName(username);

        if(possibleUser != NULL  && possibleUser->getDescription() == password) {
            cout << "User " << username << " logged on " << endl;
            possibleUser->setRoom(startingRoom);
            return possibleUser;
}
    //If there was no sucessful log on return -1
    return NULL;
}	

int newUserFunction(string username, string password) {
	//If the username is already taken then return -1 to indicate that there wasn't a new account created, else return a userId for the new user

	//Example that a username has been taken
	if(db->findPlayerByName(username) != NULL) {
        cout << "User tried to create an account with username of " << username <<". It already exists" << endl;
		return -1;
    }
	else {
        cout << "User create account with name " << username << endl;
        Player *p = new Player(username, password, -1);
        p->save();
        return p->getID();
    }
}
