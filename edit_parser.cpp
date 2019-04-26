#include "edit_parser.h"
#include "game_server.h"
#include <iostream>


using namespace std;

void EditParser::handleeditInput(GameServer *server, int id,  string command)
{
    //
    //    /setdesc <roomname> "description"
    //    /setreq <itemname> <roomname>
    //    /setreqmove <roomname> <itemname> <newroomname>
    //    /setchance <roomname> <%chance> <newroomname>
    
    
    
    // STRING DELIMITERS
    string input;
    string delimiterSpace = " ";
    string delimiterQuote = "\"";
    string delimiterLess = "<";
    string delimiterMore = ">";
    string delimiterPercent = "%";

    // DECLARING TEST MAPS
    map<string, string> rooms;
    map<string, string> items;
    //ADDED ROOMS
    rooms.insert( make_pair("Lobby", "a white room"));
    rooms.insert( make_pair("New Lobby", "a black room"));

    //ADDED ITEMS
    items.insert( make_pair("Staff", "a white staff"));


    bool running = true;
    while(running == true)
    {


        getline( cin, input);

        if(input == "commands")
        {
            // HELP
             server->printToUser(id,  "Avalible commands: \n \n");
             server->printToUser(id,  "To set/change room description - /setdesc <roomname> \"description\"");
             server->printToUser(id,  "To require an item to enter a room - /setreq <itemname> <roomname>");
             server->printToUser(id,  "To requre an item to stay in room otherwise moved - /setreqmove <roomname> <itemname> <newroomname>");
             server->printToUser(id,  "To set a chance teleportation - /setchance <roomname> <chance%> <newroomname> \n \n");
        }
        else if(input == "quit")
        {
            break;
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
            
                if(rooms.find(roomname) == rooms.end())
                {
                    server->printToUser(id, "Room not found");
                    break;
                }
                else
                {
                 
                    
                    input.erase(0, input.find(delimiterQuote) + delimiterQuote.length());
                    string description = input.substr(0, input.find(delimiterQuote));
                    input.erase(0, input.find(delimiterQuote) + delimiterQuote.length());  
                    
                    //this->setDesc(roomname, description);
                    //server->printToUser(id, "\n -- The Room " + roomname +"'s description was set to "); 

                    server->printToUser(id, "WIP");

                }
            }
            else if(command == "/setreq")
            {
               
                input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                 string itemname = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                if(items.find(itemname) == items.end())
                {
                    server->printToUser(id, "Item not found");
                    break;
                }
                else
                {
                    input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                    string roomname = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                    if(rooms.find(roomname) == rooms.end())
                    {
                        server->printToUser(id, "Room not found");
                        break;
                    }
                    else
                    {
                        //setReq(itemname, roomname);
                        //server->printToUser(id, "Required item: " + itemname + " set for room: ");
                        server->printToUser(id, "WIP");
                    }
                    
                }
            }
            else if(command == "/setreqmove")
            { 
        
                    input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                    string oldroom = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                    if(rooms.find(oldroom) == rooms.end())
                    {
                        server->printToUser(id, "Room not found");
                        break;
                    }
                    else
                    { 
                        input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                        string itemname = input.substr(0, input.find(delimiterMore));
                        input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                        
                        if(items.find(itemname) == items.end())
                        {
                            server->printToUser(id, "Item not found");
                            break;
                        }
                        else
                        {

                            input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                            string newroom = input.substr(0, input.find(delimiterMore));
                            input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                        
                            if(rooms.find(newroom) == rooms.end())
                            {
                                server->printToUser(id, "Room not found");
                                break;
                            }
                            else
                            {
                                //setreqMove(oldroom, itemname, newroom)
                                //server->printToUser(id, "Item: " + itemname + " requirement was set to " + roomname + " and will teleport you to " + newroomname);
                            
                                server->printToUser(id, "WIP");
                            }
                        }
                                   
                    }

            }
            else if(command == "/setchance")
            {
        
                    input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                    string roomname = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                    if(rooms.find(roomname) == rooms.end())
                    {
                        server->printToUser(id, "Room not found");
                        break;
                    }
                    else
                    { 
                        string percentchance = input.substr(0, input.find(delimiterMore));
                        input.erase(0, input.find(delimiterPercent) + delimiterPercent.length());
                        double chance = stod(percentchance);
                        if(chance < 0 && chance > 100)
                        {
                            server->printToUser(id, "Chance not within parameters");
                            break;
                        }
                        else
                        {
                            
                            input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                            string newroomname = input.substr(0, input.find(delimiterMore));
                            input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                        
                            if(rooms.find(roomname) == rooms.end())
                            {
                                server->printToUser(id, "Room not found");
                                break;
                            }
                            else
                            {
                                //setChance(roomname, chance, newroomname) 
                               
                                server->printToUser(id, "WIP");
                                
                                //server->printToUser(id, ("In the room " + roomname + " There is now a " + chance + " % that a player will be teleported to " + newroomname + " if entered");
                            }
                        }
                                   
                    }

            
            }
            else
            {
                 server->printToUser(id, "command not recognized try again");
            }
        }
    }
}
