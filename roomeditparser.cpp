#include <iostream>
#include <string>
#include <map>
#include <utility>



int main()
{
    //
    //    /setdesc <roomname> "description"
    //    /setreq <itemname> <roomname>
    //    /setreqmove <roomname> <itemname> <newroomname>
    //    /setchance <roomname> <%chance> <newroomname>
    
    
    
    // STRING DELIMITERS
    std::string input;
    std::string delimiterSpace = " ";
    std::string delimiterQuote = "\"";
    std::string delimiterLess = "<";
    std::string delimiterMore = ">";

    // DECLARING TEST MAPS
    std::map<std::string, std::string> rooms;
    std::map<std::string, std::string> items;
    //ADDED ROOMS
    rooms.insert(std::make_pair("Lobby", "a white room"));
    rooms.insert(std::make_pair("New Lobby", "a black room"));

    //ADDED ITEMS
    items.insert(std::make_pair("Staff", "a white staff"));



    // PROMPT
    std::cout << "Type 'help' for a list of commands" << std::endl;

    bool running = true;
    while(running == true)
    {


    getline(std::cin, input);

        if(input == "help")
        {
            // HELP
            std::cout << "Avalible commands: \n \n" << std::endl;
            std::cout << "To set/change room description - /setdesc <roomname> \"description\"" << std::endl;
            std::cout << "To require an item to enter a room - /setreq <itemname> <roomname>" << std::endl;
            std::cout << "To requre an item to stay in room otherwise moved - /setreqmove <roomname> <itemname> <newroomname>" << std::endl;
            std::cout << "To set a chance teleportation - /setchance <roomname> <chance%> <newroomname> \n \n " << std::endl;
        }
        else if(input == "quit")
        {
            return false;
        }
        else
        {
                
            std::string command = input.substr(0, input.find(delimiterSpace));
            input.erase(0, input.find(delimiterSpace) + delimiterSpace.length());

            if(command == "/setdesc")
            {
                input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                std::string roomname = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
            
                if(rooms.find(roomname) == rooms.end())
                {
                    std::cout << "Room not found" << std::endl;
                    break;
                }
                else
                {
                 
                    
                    input.erase(0, input.find(delimiterQuote) + delimiterQuote.length());
                    std::string description = input.substr(0, input.find(delimiterQuote));
                    input.erase(0, input.find(delimiterQuote) + delimiterQuote.length());
                    

                    //function setDesc(roomname, description);

                    std::cout << "\n -- The Room " << roomname << "'s description was set to " << description << std::endl;


                }
            }
            else if(command == "/setreq")
            {
               
                input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                std::string itemname = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                if(items.find(itemname) == items.end())
                {
                    std::cout << "Item not found" << std::endl;
                    break;
                }
                else
                {
                    input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                    std::string roomname = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                    if(rooms.find(roomname) == rooms.end())
                    {
                        std::cout << "Room not found" << std::endl;
                        break;
                    }
                    else
                    {
                        std::cout << "Required item: " << itemname << " set for room: " << roomname << std::endl;
                    }
                    
                }
            }
            else if(command == "/setreqmove")
            { 
        
                    input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                    std::string roomname = input.substr(0, input.find(delimiterMore));
                    input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                
                    if(rooms.find(roomname) == rooms.end())
                    {
                        std::cout << "Room not found" << std::endl;
                        break;
                    }
                    else
                    { 
                        input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                        std::string itemname = input.substr(0, input.find(delimiterMore));
                        input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                        
                        if(items.find(itemname) == items.end())
                        {
                            std::cout << "Item not found" << std::endl;
                            break;
                        }
                        else
                        {

                            input.erase(0, input.find(delimiterLess) + delimiterLess.length());
                            std::string newroomname = input.substr(0, input.find(delimiterMore));
                            input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                        
                            if(rooms.find(roomname) == rooms.end())
                            {
                                std::cout << "Room not found" << std::endl;
                                break;
                            }
                            else
                            {
                                std::cout << "Item: " << itemname << " requirement was set to " << roomname << " and will teleport you to " << newroomname << std::endl;
                            }
                        }
                                   
                    }

                    //Function setreqmove(oldRoom, item, newRoom)
            }
            else if(command == "/setchance")
            {
                std::string roomname = input.substr(0, input.find(delimiterMore));
                input.erase(0, input.find(delimiterMore) + delimiterMore.length());
                std::cout << roomname << std::endl;
            }
            else
            {
                std::cout << "command not recognized try again" << std::endl;
            }



        }

    }
}
