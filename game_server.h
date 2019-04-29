#ifndef TELNET_SERVER_H
#define TELNET_SERVER_H

// Max number of players the telnet server can handle
#define MAX_PLAYERS 25
#define DEFAULT_TELNET_PORT 2323
#define SOCKET int

//Includes the struct for the polling
#include <poll.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "libtelnet.h"
#include <vector>
#include <cstring>
#include <unistd.h>
#include <string>
class Player;
struct user_data{
	// Name of the user
	char *name;
	//ID of the user, will only be set on a sucessful log on
	int id;
    //Player pointer
    Player *player;
    //Stores the state of the player log on sequence
    int state;
	//Each user has a socket that is their network connection
	SOCKET sock;
	//Telnet struct that is the connection of the user, essentially an object, it helps abstract the details of telnet functionality
	telnet_t *telnet;
	//Libtelnet sends and recieves messages as chars using a buffer
	char linebuffer[256];
	int linepos;
};
class GameServer {
	private:
		//Write out the structs that store data within the class, these are only relevant within the class implementation
		//Store the connection information of a user  who connect to the server, only keeping track of the telnet necessary information
		//Contains the polling information for the sockets that the users are connected on
		struct pollfd *pfd;
		//Store the user data including the telnet session and the socket used for communication
		struct user_data *users;
		//Socket where the program listens for incoming connections
		SOCKET listen_sock;	
		//A middle socket structure that ties the network aspect(IPV4 and port number) into sockets which the application can communicate with
		struct sockaddr_in addr;
		//The IPV4 port to address the server from on the network
		int portNum;
		//The Return status of low level functions
		int rs;
	public:
		GameServer(int portNumber);
		GameServer();
		//This function is called whenever a user enters a string, the int is the users id
		void setCallBackFunction(void (*f)(Player*, std::string));
		//Function that will validate the user's log on information, returns -1 if invalid, else return their id
		void setLogOnFunction(int (*f)(std::string, std::string));
        void setCreateNewUserFunction(int (*f)(std::string, std::string));
		int getPortNumber() const;
		void start();
		void printToUser(Player*, std::string);
        void printToUsers(std::vector<Player*>, std::string);
        void broadcast(std::string);
};
#endif
