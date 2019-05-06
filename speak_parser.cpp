#include "speak_parser.h"
#include "game_server.h"
#include <iostream>
#include "common.h"
#include "database.h"

using namespace std;

bool SpeechParser::handlespeechInput(Player *p, string command)
{
    //      /msg Player "message"   sends a message to player if theyre online
    //      /me "messeage"          broadcasts to all online players your message
    //REGEX PATTERNS
    string input = command;
    regex msgPattern("/msg (.+) (\"([^\"]*)\")");
    
    smatch m;
    
    if(input == "help")
    {
        //Help
        server->printToUser(p, "Available Speech Commands: \n");
        server->printToUser(p, "To message another player online in the server - /msg <player> \"Message\"");
        return false;
    }

    if(regex_match(command, m, msgPattern))
    {
         if(db->findPlayerByName(m[1]) != NULL)
         {  
             server->printToUser(db->findPlayerByName(m[1]), string(p->getUsername() + " Says: \n"));
             string temp(m[3]);
             temp += "\n";
             server->printToUser(db->findPlayerByName(m[1]), temp);
             return true;
        }
         else
         {
            server->printToUser(p, "The player you are looking for is either offline or doesnt exist");
            return true;
            }
    }
    return false;
    
}
