#include "game_server.h"

#include<iostream>

using namespace std;

//Functions that will be called when user enters information
void string_from_user(int, string);
int logOnFunction(string,string);

//Global Refrence so the two functions can refrence it
GameServer *server;

int main() {
	
	//Instantiate a Game server on the defualt port 2323
	server = new GameServer();
	//Instantiate a Game server on a specific port 
	//IT NEEDS TO BE ABOVE 1024 to not require root permissions
	//server = new GameServer(2323);

	//When a user enters their credentials, they are checked with this function, the function returns a unique id
	server->setLogOnFunction(logOnFunction);
	//When a user enters a line, this function is called to handle the parsing and response generation
	server->setCallBackFunction(string_from_user);

	//Start the server
	server->start();
	
return 0;
}


void string_from_user(int id, string input){
	//When the user enters information, it will be passed as a parameter to this function
	string output = "User with id: ";
	output += std::to_string(id) + " entered \"" + input + "\"";
	cout << output << endl;
	server->printToUser(id, output);
}

int logOnFunction(string username, string password) {
	bool isCorrect = (username == "Username" && password == "Password");

	if(isCorrect)
		//Example userID
		return 100;
	else
		return -1;
}	
