#include "edit_parser.h"
#include "game_server.h"
#include <iostream>
#include "common.h"
#include "database.h"

using namespace std;

bool EditParser::handleeditInput(Player *p,  string command)
{
    //
    //    /setdesc <roomname> "description"
    //    /setreq <itemname> <roomname>
    //    /setreqmove <roomname> <itemname> <newroomname>
    //    /setchance <roomname> <%chance> <newroomname>
    
    
    
    // REGEX PATTERNS & MORE
    string input = command;
    regex setdescPattern ("/setdesc (.+) (\"([^\"]*)\")");
    regex setreqPattern ("/setreq (.+) (.+)");
    regex setreqmovePattern ("/setreqmove (.+) (.+) (.+)");
    regex setchancePattern ("/setchance (.+) ([0-99]%) (.+)");
    smatch m;
    
    //ADD CAN PLAYER EDIT

    if(input == "help")
    {
        // HELP
         server->printToUser(p,  "Available editing commands: \n \n");
         server->printToUser(p,  "To set/change room description - /setdesc <roomname> \"description\"");
         server->printToUser(p,  "To require an item to enter a room - /setreq <itemname> <roomname>");
         server->printToUser(p,  "To requre an item to stay in room otherwise moved - /setreqmove <roomname> <itemname> <newroomname>");
         server->printToUser(p,  "To set a chance teleportation - /setchance <roomname> <chance%> <newroomname> \n \n");
    return false;
    }
    

        if(regex_match(command, m, setdescPattern)){
        {
            server->printToUser(p, m[1]);
            server->printToUser(p, m[3]);
            
            if(db->findRoomByName(m[1]) != NULL)
            { 
                db->findRoomByName(m[1])->setDesc(m[3]);   
            }
            else
            {
             
                server->printToUser(p, "Room not found");
              
            }
        }
        if(regex_match(command, m, setreqPattern))
        {
            if(db->findItemByName(m[1]) == NULL)
            {
                server->printToUser(p, "Item not found");
            }
            else
            {
                if(db->findRoomByName(m[2]) == NULL)
                {
                    server->printToUser(p, "Room not found");
                }
                else
                {
                    db->findRoomByName(m[2])->setReq(m[1]);
                }
                
            }
        }
        if(regex_match(command, m, setreqmovePattern))
        {  
                if(db->findRoomByName(m[1]) == NULL)
                {
                    server->printToUser(p, "First Room Parameter not found");
                }
                else
                { 
                    if(db->findItemByName(m[2]) == NULL)
                    {
                        server->printToUser(p, "Item not found");
                    }
                    else
                    {
                        if(db->findRoomByName(m[3]) == NULL)
                        {
                            server->printToUser(p, "Room not found");
                        }
                        else
                        {
                            //setreqMove(oldroom, itemname, newroom)
                            //server->printToUser(p, "Item: " + itemname + " requirement was set to " + roomname + " and will teleport you to " + newroomname);
                        
                            server->printToUser(p, "WIP");
                        }
                    }
                               
                }

        }
        if(regex_match(command, m, setchancePattern))
        {
                if(db->findRoomByName(m[1]) == NULL)
                {
                    server->printToUser(p, "Room not found");
                }
                else
                {
                    double chance = stod(m[2]);
                    if(chance < 0 && chance > 100)
                    {
                        server->printToUser(p, "Chance not within parameters");
                    }
                    else
                    {
                        if(db->findRoomByName(m[3]) == NULL)
                        {
                            server->printToUser(p, "Room not found");
                        }
                        else
                        {
                            //setChance(roomname, chance, newroomname) 
                           
                            server->printToUser(p, "WIP");
                            
                            //server->printToUser(p, ("In the room " + roomname + " There is now a " + chance + " % that a player will be teleported to " + newroomname + " if entered");
                        }
                    }
                               
                }

        
        }
    }
        return false;
}
