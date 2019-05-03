#include "game_server.h"
#include "common.h"
#include "player.h"
#include "database.h"
#include <iostream>
#include <cstring>
#include "player.h"

using namespace std;

//TODO - Is there a better way to do the call back function?
static void (*cbs)(Player*, string);
static Player* (*logOnCheck)(string,string);
static int (*createNewUser)(string,string);
/* The ststic type in C tells the compiler that the function should not be accesible outside of this .cpp file
 * This function takes an integer repersenting the socket, the buffer of characters to send, and the amount of 
 * characters in the buffer to send
 */
static void _send(SOCKET sock, const char *buffer, size_t size) {
	int rs;

	/* ignore on invalid socket */
	if (sock == -1)
		return;

	/* send data */
	while (size > 0) {
		//TODO - Figure out why this uses send instead of telnet_printf()
		if ((rs = send(sock, buffer, (int)size, 0)) == -1) {
			if (errno != EINTR && errno != ECONNRESET) {
				fprintf(stderr, "send() failed: %s\n", strerror(errno));
				exit(1);
			} else {
				return;
			}
		} else if (rs == 0) {
			fprintf(stderr, "send() unexpectedly returned 0\n");
			exit(1);
		}

		/* update pointer and size to see if we've got more to send */
		buffer += rs;
		size -= rs;
	}
}

//Struct that defines the kind of features our telnet supports
static const telnet_telopt_t telopts[] = {
	{ TELNET_TELOPT_COMPRESS2,	TELNET_WILL, TELNET_DONT },
	{ -1, 0, 0 }
};


/* process input line */
static void _online(const char *line, size_t overflow, void *ud) {
	struct user_data *user = (struct user_data*)ud;
	//int i;
	(void)overflow;

	//If the user has a state of -1 then they are selecting whether they want to log on or create an account
	if (user->state == -1) {
		 if(strcmp(line, "n") == 0) {
            telnet_printf(user->telnet, "Enter your username: ");
            user->state = 0;
		} else if(strcmp(line, "l") == 0) {
            user->state = 1;
            telnet_printf(user->telnet, "Enter your username : ");
        }else{
			telnet_printf(user->telnet, "Invalid option \nPlease enter an option (n for new account, l for log on) > ");
		}
		return;
    //User is trying to create an account
	} else if(user->state == 0) {
        if(user->name == NULL) {
            if(strcmp(line, "") == 0){
                telnet_printf(user->telnet, "Invalid Username, please try again\nEnter your username: ");
                return;
            }
            user->name = strdup(line);
            telnet_printf(user->telnet, "Enter your password: ");
			telnet_negotiate(user->telnet, TELNET_WILL, TELNET_TELOPT_ECHO);
            return;
        }
        else {
            if(strcmp(line, "") == 0){
                telnet_printf(user->telnet, "Invalid Passowrd, please try again\nEnter your password: ");
                return;
            }
            int userId = createNewUser(user->name, line);
            if(userId == -1) {
                telnet_printf(user->telnet, "\nA user already exists with this username, please enter a different one\nEnter your username: ");
			    telnet_negotiate(user->telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
                free(user->name);
                user->name = NULL;
                return;
            } else {
                user->id = userId;
                user->player = db->findPlayerById(user->id);
                user->state = 2;
			    telnet_negotiate(user->telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
            telnet_printf(user->telnet,"\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n/////////#&@@@&(///////////////////&@@@@%%///////////////////#&@@@@%%//////////////////#%%#(////////(##////////////////(%%#(////////(#%%(//////\n///////@@&/////@@&//////////////(@@(////#@@///////////////@@%%/////#@@///////////////@@%%#@@/////&@&(@@///////////////@@(@@/////(@@(@@//////\n///////@@///////@@//////////////@@(//////%%@%%/////////////#@&///////#@&//////////////@@//&@(////@@//@@///////////////@@/(@&////@@//@@//////\n///////@@///////////////////////@@(//////%%@%%/////////////#@&///////#@&//////////////@@///@@///&@(//@@///////////////@@//@@///(@&//@@//////\n///////@@&//////////////////////@@(//////%%@%%/////////////#@&///////#@&//////////////@@///&@(//@@///@@///////////////@@//(@&//@@///@@//////\n/////////#@@@@@@%%///////////////@@(((((%%@@@//////////////#@@%%%%%%%%%%%%%%&@&//////////////@@////@@/%%@(///@@///////////////@@///@@/(@&///@@//////\n////////////////@@//////////////@@((###(/////////////////#@&(((((((%%@&//////////////@@////%%@(@@////@@///////////////@@///(@&@@////@@//////\n//////(&(///////@@(/////////////@@(//////////////////////#@&///////#@&//////////////@@/////@@@(////@@///////////////@@////@@@&////@@//////\n//////%%@%%///////@@(/////////////@@(//////////////////////#@&///////#@&//////////////@@/////%%@@/////@@///////////////@@////(@@/////@@//////\n///////&@@@@@@@@@#//////////////@@(//////////////////////#@&///////#@&//////////////@@/////////////@@///////////////@@////////////@@//////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
			telnet_printf(user->telnet, "Welcome To SPAMM\n");
            }
        }
    //The user is logging on
	} else if(user->state == 1) {
        if(user->name == NULL){
            if(strlen(line) == 0){
                telnet_printf(user->telnet, "Invalid username, please enter a valid username\nEnter your username : ");
                return;
            }
            user->name = strdup(line);
            telnet_printf(user->telnet, "Enter your password : ");
			telnet_negotiate(user->telnet, TELNET_WILL, TELNET_TELOPT_ECHO);
            return;
        }
        else {
            //Password was entered, display newline to put new messges on the next line
            telnet_printf(user->telnet, "\n");
            if(strlen(line) == 0){
                telnet_printf(user->telnet, "Please enter a password\n: ");
                return;
            }
            Player* loggedOnUser = logOnCheck(user->name, line);
            if (loggedOnUser == NULL){
                telnet_printf(user->telnet, "Invalid username or password. Try again\nEnter Username: ");
                free(user->name);
                user->name = NULL;
			    telnet_negotiate(user->telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
                return;
            } else {
                user->id = loggedOnUser->getID();
                user->player = loggedOnUser;
                //User is logged on, out of authentication state
                //Get Player*
                user->state = 2;
                //Display Welcome Message
            telnet_printf(user->telnet,"//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n/////////#&@@@&(///////////////////&@@@@%%///////////////////#&@@@@%%//////////////////#%%#(////////(##////////////////(%%#(////////(#%%(//////\n///////@@&/////@@&//////////////(@@(////#@@///////////////@@%%/////#@@///////////////@@%%#@@/////&@&(@@///////////////@@(@@/////(@@(@@//////\n///////@@///////@@//////////////@@(//////%%@%%/////////////#@&///////#@&//////////////@@//&@(////@@//@@///////////////@@/(@&////@@//@@//////\n///////@@///////////////////////@@(//////%%@%%/////////////#@&///////#@&//////////////@@///@@///&@(//@@///////////////@@//@@///(@&//@@//////\n///////@@&//////////////////////@@(//////%%@%%/////////////#@&///////#@&//////////////@@///&@(//@@///@@///////////////@@//(@&//@@///@@//////\n/////////#@@@@@@%%///////////////@@(((((%%@@@//////////////#@@%%%%%%%%%%%%%%&@&//////////////@@////@@/%%@(///@@///////////////@@///@@/(@&///@@//////\n////////////////@@//////////////@@((###(/////////////////#@&(((((((%%@&//////////////@@////%%@(@@////@@///////////////@@///(@&@@////@@//////\n//////(&(///////@@(/////////////@@(//////////////////////#@&///////#@&//////////////@@/////@@@(////@@///////////////@@////@@@&////@@//////\n//////%%@%%///////@@(/////////////@@(//////////////////////#@&///////#@&//////////////@@/////%%@@/////@@///////////////@@////(@@/////@@//////\n///////&@@@@@@@@@#//////////////@@(//////////////////////#@&///////#@&//////////////@@/////////////@@///////////////@@////////////@@//////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
			telnet_printf(user->telnet, "Welcome To SPAMM\n> ");
			telnet_negotiate(user->telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
            return;
            }
        }
    }
	//If the user has a name but no id, they have not been authenticated, this line is their password
//	if (user->id == -1) {
//		int userId = logOnCheck(user->name, line);
//
		//Print newline so any message is not on the same line as the "Enter Password:" prompt
//		telnet_printf(user->telnet, "\n");

	// 	if(userId != -1){
      // 	telnet_negotiate(user->telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
      //      telnet_printf(user->telnet,"//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n/////////#&@@@&(///////////////////&@@@@%///////////////////#&@@@@%//////////////////#%#(////////(##////////////////(%#(////////(#%(//////\n///////@@&/////@@&//////////////(@@(////#@@///////////////@@%/////#@@///////////////@@%#@@/////&@&(@@///////////////@@(@@/////(@@(@@//////\n///////@@///////@@//////////////@@(//////%@%/////////////#@&///////#@&//////////////@@//&@(////@@//@@///////////////@@/(@&////@@//@@//////\n///////@@///////////////////////@@(//////%@%/////////////#@&///////#@&//////////////@@///@@///&@(//@@///////////////@@//@@///(@&//@@//////\n///////@@&//////////////////////@@(//////%@%/////////////#@&///////#@&//////////////@@///&@(//@@///@@///////////////@@//(@&//@@///@@//////\n/////////#@@@@@@%///////////////@@(((((%@@@//////////////#@@%%%%%%%%%%%%%%&@&//////////////@@////@@/%@(///@@///////////////@@///@@/(@&///@@//////\n////////////////@@//////////////@@((###(/////////////////#@&(((((((%@&//////////////@@////%@(@@////@@///////////////@@///(@&@@////@@//////\n//////(&(///////@@(/////////////@@(//////////////////////#@&///////#@&//////////////@@/////@@@(////@@///////////////@@////@@@&////@@//////\n//////%@%///////@@(/////////////@@(//////////////////////#@&///////#@&//////////////@@/////%@@/////@@///////////////@@////(@@/////@@//////\n///////&@@@@@@@@@#//////////////@@(//////////////////////#@&///////#@&//////////////@@/////////////@@///////////////@@////////////@@//////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////\n");
	//		telnet_printf(user->telnet, "Welcome To SPAMM\n> ");
	//		user->id = userId;
	//		return;
	//	} else {
	//		telnet_negotiate(user->telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
	//		telnet_printf(user->telnet, "Invalid Username or Password, Try again \nEnter Username: ");
	//		user->name = 0;
	//		return;
	//	}
	//}

	/* if line is "quit" then, well, quit */
	if (strcmp(line, "quit") == 0) {
        cout << user->name << " logged off " << endl;
		close(user->sock);
		user->sock = -1;
		//_message(user->name, "** HAS QUIT **");
		free(user->name);
		user->name = 0;
		user->id   = -1;
        user->state = -1;
		return;
	}
	//If its not a log on or a quit command, pass it to the callback function for the game to figure out how to process it

	cbs(user->player, line);
    //Print the prompt for user input
    telnet_printf(user->telnet, "> ");
}

static void linebuffer_push(char *buffer, size_t size, int *linepos,
		char ch, void (*cb)(const char *line, size_t overflow, void *ud),
		void *ud) {

	/* CRLF -- line terminator */
	if (ch == '\n' && *linepos > 0 && buffer[*linepos - 1] == '\r') {
		/* NUL terminate (replaces \r in buffer), notify app, clear */
		buffer[*linepos - 1] = 0;
		cb(buffer, 0, ud);
		*linepos = 0;

	/* CRNUL -- just a CR */
	} else if (ch == 0 && *linepos > 0 && buffer[*linepos - 1] == '\r') {
		/* do nothing, the CR is already in the buffer */

	/* anything else (including technically invalid CR followed by
 * 	 * anything besides LF or NUL -- just buffer if we have room
 * 	 	 * \r
 * 	 	 	 */
	} else if (*linepos != (int)size) {
		buffer[(*linepos)++] = ch;

	/* buffer overflow */
	} else {
		/* terminate (NOTE: eats a byte), notify app, clear buffer */
		buffer[size - 1] = 0;
		cb(buffer, size - 1, ud);
		*linepos = 0;
	}
}

static void _input(struct user_data *user, const char *buffer,
		size_t size) {
	unsigned int i;
	for (i = 0; i != size; ++i)
		linebuffer_push(user->linebuffer, sizeof(user->linebuffer), &user->linepos,
				(char)buffer[i], _online, user);
}


//Gets called when telnet has an event occur
static void _event_handler(telnet_t *telnet, telnet_event_t *ev,
		void *user_data) {
	struct user_data *user = (struct user_data*)user_data;

	switch (ev->type) {
	/* data received */
	case TELNET_EV_DATA:
		_input(user, ev->data.buffer, ev->data.size);
	break;
	/* data must be sent */
	case TELNET_EV_SEND:
		_send(user->sock, ev->data.buffer, ev->data.size);
		break;
	/* enable compress2 if accepted by client */
	case TELNET_EV_DO:
		if (ev->neg.telopt == TELNET_TELOPT_COMPRESS2)
			telnet_begin_compress2(telnet);
		break;
	/* error */
	case TELNET_EV_ERROR:
		close(user->sock);
		user->sock = -1;
		if (user->name != 0) {
			//_message(user->name, "** HAS HAD AN ERROR **");
			free(user->name);
			user->name = 0;
		}
		telnet_free(user->telnet);
		break;
	default:
		/* ignore */
		break;
	}
}





GameServer::GameServer(int portNumber) : portNum(portNumber) {
	std::cout << "Attemping to listen on: " << portNum << std::endl;
	//Changed from arrays to vectors, trying that change out
	//Initalize all values of these struct arrays to 0
	//memset(&pfd, 0, sizeof(pfd));
	//memset(users, 0, sizeof(users));

	//NOTE - I don't thing I need to do this because I am using a vector instead of an array
	//Set the sockets of the users to -1, indicating that no user is currently connected
	/*for (int i = 0; i != MAX_PLAYERS; ++i)
	*	users[i].sock = -1;
	*/ 
	/* Initalize a socket based on the linux socket man pagess
 	 * AF_INET = This socket is expecting to listen to devices on the internet using IPV4 protocols
 	 * SOCK_STREAM = Use this as a two way connection
 	 */ 
	if ((listen_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		fprintf(stderr, "socket() failed: %s\n", strerror(errno));
		return;
	} 
	/* reuse address option */
	//TODO - Figure out where the documentation for this is
	rs = 1;
	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&rs, sizeof(rs));

	/* bind to listening addr/port */
	memset(&addr, 0, sizeof(addr));
	//Set the speficiations of the network socket
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	//Set the desired port number for the socket
	addr.sin_port = htons(portNum);
	//Attempt to bind the socket to the port
	if (bind(listen_sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
		fprintf(stderr, "bind() failed: %s\n", strerror(errno));
		close(listen_sock);
		return;
	}

	/* listen for clients */
	if (listen(listen_sock, 5) == -1) {
		fprintf(stderr, "listen() failed: %s\n", strerror(errno));
		close(listen_sock);
		return;
	}
	
	std::cout << "Listening successful" << std::endl;
	//Initalize arrays
	users = new user_data[MAX_PLAYERS];
	pfd = new pollfd[MAX_PLAYERS + 1];

}

GameServer::GameServer() : GameServer(DEFAULT_TELNET_PORT){}


void GameServer::start() {
	int returnStatus;
	socklen_t addrlen;
	int i;
	SOCKET client_sock;
	char buffer[512];
	//Initalize the listening socket for incoming connections
	pfd[MAX_PLAYERS].fd = listen_sock;
	pfd[MAX_PLAYERS].events = POLLIN;
	//Loop through and set all users sockets to -1 and their id to -1
	for(i = 0; i != MAX_PLAYERS; ++i){
		users[i].sock   = -1;
		users[i].id     = -1;
        users[i].player = NULL;
        users[i].state  = -1;
        users[i].name   = NULL;
	}

	//Loop forever and handle input
	for(;;) {
		/*Prepare for a socket connection to have data ready to recieve*/
		for (i = 0; i != MAX_PLAYERS; ++i) {
			if (users[i].sock != -1) {
				pfd[i].fd = users[i].sock;
				pfd[i].events = POLLIN;
			} else {
				pfd[i].fd = -1;
				pfd[i].events = 0;
			}
		}
		//Wait until any of the connected users create any events, or the 'listen_sock' has an event
		returnStatus = poll(pfd, MAX_PLAYERS + 1, -1);
		
		//Error		
		if (returnStatus == -1 && errno != EINTR) {
			fprintf(stderr, "poll() failed: %s\n", strerror(errno));
			close(listen_sock);
			return;
		}
		
		//If the 'listen_socket' has data to read, meaning there is a new connection
		if (pfd[MAX_PLAYERS].revents & POLLIN) {
			/* accept the sock */
			addrlen = sizeof(addr);
			if ((client_sock = accept(listen_sock, (struct sockaddr *)&addr,
					&addrlen)) == -1) {
				fprintf(stderr, "accept() failed: %s\n", strerror(errno));
				return;
			}
			//The new connection was successful
			std::cout << "Connection received" << std::endl;
			
			//Find an empty spot and add the socket to the array
			/* find a free user */
			for (i = 0; i != MAX_PLAYERS; ++i)
				if (users[i].sock == -1)
					break;
			if (i == MAX_PLAYERS) {
				printf("  rejected (too many users)\n");
				_send(client_sock, "Too many users.\r\n", 14);
				close(client_sock);
			}
			/* init, welcome */
			users[i].sock = client_sock;
			users[i].telnet = telnet_init(telopts, _event_handler, 0,
					&users[i]);
			telnet_negotiate(users[i].telnet, TELNET_WILL, TELNET_TELOPT_COMPRESS2);
			telnet_negotiate(users[i].telnet, TELNET_WONT, TELNET_TELOPT_ECHO);
			telnet_printf(users[i].telnet, "Enter option (n for new account, l for log on)\n>  ");
		}	
			/* read from client */
		for (i = 0; i != MAX_PLAYERS; ++i) {
			/* skip users that aren't actually connected */
			if (users[i].sock == -1)
				continue;

			if (pfd[i].revents & POLLIN) {
				if ((rs = recv(users[i].sock, buffer, sizeof(buffer), 0)) > 0) {
					//Push the received socket data into telnet and let the event handling take care of it
					telnet_recv(users[i].telnet, buffer, rs);
				} else if (rs == 0) {
					printf("Connection closed.\n");
					close(users[i].sock);
					if (users[i].name != 0) {
						//_message(users[i].name, "** HAS DISCONNECTED **");
						free(users[i].name);
						users[i].name = 0;
					}
					telnet_free(users[i].telnet);
					users[i].sock = -1;
					break;
				} else if (errno != EINTR) {
					fprintf(stderr, "recv(client) failed: %s\n",
							strerror(errno));
					exit(1);
				}
			}
		}
	}
}

void GameServer::setCallBackFunction(void (*f)(Player*,string)){
	cbs = f; 
}
void GameServer::setLogOnFunction(Player* (*f) (string,string)){
	logOnCheck = f; 
}
void GameServer::printToUser(Player *p, string message){
	int i ;
	message +=  "\n";
	for(i = 0; i != MAX_PLAYERS; ++i)
		if(users[i].player == p)
			break;
	telnet_printf(users[i].telnet, message.c_str());
}
void GameServer::printToUsers(vector<Player*> players, string message){
    for(unsigned int i = 0; i < players.size(); ++i)
       printToUser(players[i], message);
}
void GameServer::broadcast(std::string message) {
    for(int i = 0; i != MAX_PLAYERS; ++i)
        if(users[i].id != -1)
            telnet_printf(users[i].telnet, message.c_str());
}
void GameServer::setCreateNewUserFunction(int (*f)(string,string)) {
    createNewUser = f;
}
void GameServer::stop() {
      
}
