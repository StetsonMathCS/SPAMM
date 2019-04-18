#include <iostream>
using namespace std;

#include "parser.h"
#include "player.h"
#include "room.h"
#include "gamemap.h"


int main() {

    Room* lab = new Room;
    lab->setName("Dr. Sam Beckett's lab");
    lab->setDescription("A large room with a super hybrid computer named Ziggy. A room called the project accelerator is seen to the north.");
   
    Room* accelerator = new Room;
    accelerator->setName("the Project Accelerator");
    accelerator->setDescription("A small room where someone can quantum leap once the project is finished. A bright light suddenly flashes.");
   
    Room* xfiles = new Room;
    xfiles->setName("Mulder's Office");
    xfiles->setDescription("A dark basement with stacks of files labeled classified and a poster on the wall featuring a UFO that says I want to believe. A man named Mulder comes in and tells you that you have a case to investigate in Florida.");
    
    Room* sunnydale = new Room;
    sunnydale->setName("Sunnydale");
    sunnydale->setDescription("Something strange is going on here. An English man named Giles, a red head named Willow, a guy named Xander, and a bleach blonde British guy are all talking to you about some ancient evil called The First and tell you to go with them.");
   
    Room* grimmauld = new Room;
    grimmauld->setName("12 Grimmauld Place");
    grimmauld->setDescription("A room with a long table with people sitting around it, you catch some of their names, Arthur, Sirius, and Remus. They are discussing the safety of someone called Harry and refer to themselves as the Order of the Phoenix.");

    Room* trek  = new Room;
    trek->setName("the Starship Enterprise");
    trek->setDescription("The bridge of a starship apparently called Enterprise. There is a southern Doctor named McCoy who appears to be irritated with a man that has pointy ears called Spock. Meanwhile, what seems to be the captain of the ship is sitting back laughing.");

    Room* tardis = new Room;
    tardis->setName("the TARDIS");
    tardis->setDescription("A large room that has a console and a glowing blue light above it. A man in converses runs in rambling about time.");

    Room* firefly = new Room;
    firefly->setName("Serenity"); 
    firefly->setDescription("A ship that looks sort of rundown. There is a ragtag group of people who appear to be the crew.");

    Room* sherlock = new Room;
    sherlock->setName("221B Baker St.");
    sherlock->setDescription("A room filled with odd objects including a skull. Two men, one short with light hair and the other tall with dark hair, are seen arguing over some apparent gunshot holes in the wall");

    Room* jl = new Room;
    jl->setName("the Watchtower"); 
    jl->setDescription("A satellite in orbit over Earth. There are many people here dressed as superheroes all being addressed by a man called Batman about the findings of another person called The Question");

    Room* empty = new Room;
    empty->setName("empty");

    GameMap* gm = new GameMap;

    gm->setAdjacent(lab, accelerator, "north");

    gm->setAdjacent(accelerator, xfiles, "north");
    gm->setAdjacent(accelerator, sunnydale, "east");
    gm->setAdjacent(accelerator, trek, "south");
    gm->setAdjacent(accelerator, grimmauld, "west");

    gm->setAdjacent(xfiles, sunnydale, "north");
    gm->setAdjacent(xfiles, grimmauld, "east");
    gm->setAdjacent(xfiles, tardis, "south");
    gm->setAdjacent(xfiles, empty, "west");

    gm->setAdjacent(sunnydale, jl, "north");
    gm->setAdjacent(sunnydale, firefly, "east");
    gm->setAdjacent(sunnydale, empty, "south");
    gm->setAdjacent(sunnydale, sherlock, "west");

    gm->setAdjacent(grimmauld, xfiles, "north");
    gm->setAdjacent(grimmauld, empty, "east");
    gm->setAdjacent(grimmauld, trek, "south");
    gm->setAdjacent(grimmauld, firefly, "west");

    gm->setAdjacent(trek, tardis, "north");
    gm->setAdjacent(trek, sherlock, "east");
    gm->setAdjacent(trek, jl, "south");
    gm->setAdjacent(trek, empty, "west");
	
    gm->setAdjacent(tardis, firefly, "north");
    gm->setAdjacent(tardis, sherlock, "east");
    gm->setAdjacent(tardis, empty, "south");
    gm->setAdjacent(tardis, trek, "west");

    gm->setAdjacent(firefly, tardis, "north");
    gm->setAdjacent(firefly, empty, "east");
    gm->setAdjacent(firefly, grimmauld, "south");
    gm->setAdjacent(firefly, sunnydale, "west");

    gm->setAdjacent(sherlock, jl, "north");
    gm->setAdjacent(sherlock, sherlock, "east");
    gm->setAdjacent(sherlock, xfiles, "south");
    gm->setAdjacent(sherlock, empty, "west");

    gm->setAdjacent(jl, empty, "north");
    gm->setAdjacent(jl, firefly, "east");
    gm->setAdjacent(jl, xfiles, "south");
    gm->setAdjacent(jl, grimmauld, "west");
    
    Player* player = new Player;
    player->setCurrentContainer(lab);

    Item* ziggy = new Item;
    ziggy->setLongName("ZiggyHandlink");
    lab->addToContainer(ziggy);

    Item* badge = new Item;
    badge->setLongName("FBIbadge");
    xfiles->addToContainer(badge);

    Item* stake = new Item;
    stake->setLongName("WoodenStake");
    sunnydale->addToContainer(stake);

    Item* wand = new Item;
    wand->setLongName("wand");
    grimmauld->addToContainer(wand);

    Item* broom = new Item;
    broom->setLongName("broom");
    grimmauld->addToContainer(broom);

    Item* screwdriver = new Item;
    screwdriver->setLongName("SonicScrewdriver");
    tardis->addToContainer(screwdriver);

    Item* jacket = new Item;
    jacket->setLongName("LeatherJacket");
    tardis->addToContainer(jacket);

    Item* vera = new Item;
    vera->setLongName("Vera");
    firefly->addToContainer(vera);

    Parser p;
    cout << endl;
    cout << endl;
    cout << "Welcome to the Quantum Leap project! I'm Doctor Sam Beckett and this is my friend Al." << endl;
    cout << "What's your name?" << endl;
    cout << "-> ";
    string name;
    cin >> name;
    player->setLongName(name);
    cout << endl;
    cout << "Nice to formally meet you " << player->getLongName() << ", we've heard great things about you and we think you may be able to help us smooth out the final issues with the project. If someone were to try and quantum leap now they may be hopped around all over time! Go ahead and take a look around, we'll start working once you've got your bearings." << endl;
    cout << endl;
    cout << "You're in " << lab->getName() << endl;
    cout << "Type 'help' and Ziggy will provide you with a list of commands" << endl;
    cout << lab->getDescription() << endl;
    cout << endl;
    
    while(p.handleInput(player, gm));

    return 0;
}
