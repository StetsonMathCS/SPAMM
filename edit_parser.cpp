#include "edit_parser.h"
#include "game_server.h"
#include <iostream>
#include "common.h"
#include "database.h"

using namespace std;

void EditParser::handleeditInput(Player *p,  string command)
{
    //
    //    /setdesc <roomname> "description"
    //    /setreq <itemname> <roomname>
    //    /setreqmove <roomname> <itemname> <newroomname>
    //    /setchance <roomname> <%chance> <newroomname>
    
    
    
    // STRING DELIMITERS
    string input = command;
    string delimiterSpace = " ";
    string delimiterQuote = "\"";
    string delimiterLess = "<";
    string delimiterMore = ">";
    string delimiterPercent = "%";


    if(input == "commands")
    {
        // HELP
         server->printToUser(p,  "Available editing commands: \n \n");
         server->printToUser(p,  "To set/change room description - /setdesc <roomname> \"description\"");
         server->printToUser(p,  "To require an item to enter a room - /setreq <itemname> <roomname>");
         server->printToUser(p,  "To requre an item to stay in room otherwise moved - /setreqmove <roomname> <itemname> <newroomname>");
         server->printToUser(p,  "To set a chance teleportation - /setchance <roomname> <chance%> <newroomname> \n \n");
    }
    else
    {
            
        string command = input.substr(0, input.find(delimiterSpace));
        input.erase(0, input.find(delimiterSpace) + delimiterSpace.length());

        if(command == "/setdesc")
        {
            input.erase(0, input.find(delimiterLess) + delimiterLess.length());
            string roomname = input.substr(0, input.find(delimiterMore));
            input.erase(0, input.find(delimiterMore) + delimiterMore.length());
        
            if(db->findRoomByName(roomname) == NULL)
            {
                server->printToUser(p, "Room not found");
            }
            else
            {
             
                
                input.erase(0, input.find(delimiterQuote) + delimiterQuote.length());
                string description = input.substr(0, input.find(delimiterQuote));
                input.erase(0, input.find(delimiterQuote) + delimiterQuote.length());  
                
                //this->setDesc(roomname, description);
                //server->printToUser(p, "\n -- The Room " + roomname +"'s description was set to "); 

                server->printToUser(p, "WIP");

            }
        }
        else if(command == "/setreq")
        {
           
            input.erase(0, input.find(delimiterLess) + delimiterLess.length());
             string itemname = input.substr(0, input.find(delimiterMore));
            input.erase(0, input.find(delimiterMore) + delimiterMore.length());
            
            if(db->findItemByName(itemname) == NULL)
            {
                server->printToUser(p, "Item not found");
            }
            else
            {
                input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                string roomname = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
            
                if(db->findRoomByName(roomname) == NULL)
                {
                    server->printToUser(p, "Room not found");
                }
                else
                {
                    //setReq(itemname, roomname);
                    //server->printToUser(p, "Required item: " + itemname + " set for room: ");
                    server->printToUser(p, "WIP");
                }
                
            }
        }
        else if(command == "/setreqmove")
        { 
    
                input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                string oldroom = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
            
                if(db->findRoomByName(oldroom) == NULL)
                {
                    server->printToUser(p, "First Room Parameter not found");
                }
                else
                { 
                    input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                    string itemname = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                    
                    if(db->findItemByName(itemname) == NULL)
                    {
                        server->printToUser(p, "Item not found");
                    }
                    else
                    {

                        input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                        string newroom = input.substr(0, input.find(delimiterMore));
                        input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                    
                        if(db->findRoomByName(newroom) == NULL)
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
        else if(command == "/setchance")
        {
    
                input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                string roomname = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
            
                if(db->findRoomByName(roomname) == NULL)
                {
                    server->printToUser(p, "Room not found");
                }
                else
                { 
                    string percentchance = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterPercent) + delimiterPercent.length());
                    double chance = stod(percentchance);
                    if(chance < 0 && chance > 100)
                    {
                        server->printToUser(p, "Chance not within parameters");
                    }
                    else
                    {
                        
                        input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                        string newroomname = input.substr(0, input.find(delimiterMore));
                        input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                    
                        if(db->findRoomByName(newroomname) == NULL)
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
}
