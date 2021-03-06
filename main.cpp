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
Room *startingRoom;

using namespace std;

//Functions that will be called when user enters information
Player* logOnFunction(string,string);
int newUserFunction(string,string);

//Signal handling
void exitHandler(int);

//Default starting room
void parseInput(Player *p, string input) {
    //Print the users input so it can be used for debugging purposes
    cout << p->getUsername() << " said : " << input << endl;
    if(SpeechParser::handlespeechInput(p, input))
    {
        return;
    }
    if(ActionParser::handleInput(p, input))
    {
        return;
    } 
    if(BuildParser::handleInput(p, input))
    {
        return;
    }
    if(EditParser::handleeditInput(p, input))
    {
        return;
    }
    server->printToUser(p, string("Invalid Command: " + input));
}

int main(int argc, char **argv) {
    //Default starting room
	db = new Database();
    if(db->lastid == -1) {
        startingRoom = new Room("Lobby", "The starting room");
        startingRoom->save();
    } else {
        auto rooms  = db->getRooms();
        for(auto it = rooms.begin(); it != rooms.end(); ++it) {
            if((*it)->isStartingRoom()){
                startingRoom = *it;
                break;
            }
        }
        startingRoom = new Room("Lobby", "The starting room");
        startingRoom->save();
    }
	//Instantiate a Game server on the defualt port 2323
	int port = 2323;
    if(argc == 2) {
        port = atoi(argv[1]);
    }
    server = new GameServer(port);


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
