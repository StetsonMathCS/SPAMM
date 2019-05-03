#include "speak_parser.h"
#include "game_server.h"
#include <iostream>
#include "common.h"
#include "database.h"

using namespace std;

void SpeechParser::handlespeechInput(Player *p, string command)
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
        server->printToUser(p, "Avalible Speech Commands: \n");
        server->printToUser(p, "To message another player online in the server - /msg <player> \"Message\"");
    }

    if(regex_match(command, m, msgPattern))
    {
         if(db->findPlayerByName(m[1]) != NULL)
         {
             server->printToUser(db->findPlayerByName(m[1]), m[3]);
         }
         else
         {
            server->printToUser(p, "The player you are looking for is either offline or doesnt exist");
         }
    }
    
}
