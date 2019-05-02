#!/bin/bash
echo Loading Game
echo create room Main Hall desc You and your partner have been teleported to the main hall of an enemy ship. You are here to commandeer, but know almost nothing of this misterious enemy. You prepare to delve into the darkness ahead. Maybe you should try to find a source of light before moving ahead. 
echo create item Gas Lantern desc A peculiar place to find such an antiquated item. You remember learning that the last Earthlings had to rely on these devices after the devistation. At least it works.
echo set item Gas Lantern perplayer
echo put item Gas Lantern in room Main Hall


echo create room Observation Deck desc The Observation deck seems to have been ravaged by some beast. The mess of the deck is juxtaposed by the beauty of the endless frontier that can be viewed through the main window. The void entices you to leave, and transfer back to your ship so that you might live to disover what lies beyond. 
echo connect room Observation Deck to Main Hall via east
echo connect room Main Hall to Observation Deck via west
echo create item Pipe Shotgun desc Another curious find. Have you stumbled upon the ship of a collector of some kind?
echo set item Pipe Shotgun perplayer
echo put item Pipe Shotgun in room Observation Deck


echo create room Armory desc The armory is the only lit room that can be seen, but is stripped clean of all weapons. Only used shell casings populate the floor. What did these people encounter? 
echo connect room Armory to Main Hall via west
echo connect room Main Hall to Armory via east
echo create item Beast Head desc A festering head of a monster. Where did it come from? You have never seen anything like it before. 
echo set item Beast Head unique
echo put Beast Head in room Armory 


echo create room Officer Quarters desc An array of doors labelled with the names of officers. Are those Earthling names? You recognize such names from learning about your human heritage in school. 
echo connect room Officer Quarters to Main Hall via north
echo connect room Main Hall to Officer Quarters via south
echo create item Cutlass desc A steel weapon from the Pre-Devistation period of Earth. 
echo set item Cutlass perplayer
echo put item Cutlass in room Officer Quarters


echo create room Environment Chamber desc A room mimicking the conditions of a desert. You don't like sand. It's coarse and rough and irritating and gets everywhere. Ahead, something protrudes from the sand.  
echo connect room Environment Chamber to Officer Quarters via east
echo connect room Officer Quarters to Environment Chamber via west
echo create item Shard Blade desc The massive blade stand almost as tall as yourself, but is almost weightless too. As you touch the blade screams fill your ears.
echo set item Shard Blade unique
echo put item Shard Blade in room Environment Chamber


echo create room Laboratory desc A simple laboratory. Everything is in its place... Strange. 
echo connect room Laboratory to Officer Quarters via west
echo connect room Officer Quarters to Laboratory via east
echo create item Alien Idol desc A minniature alien statue. Seems to almost take the shape of a key...
echo set item Alien Idol unique
echo put item Alien Idol in room Laboratory 

 
echo create room Escape Pods desc You see a row of executed escape pods. There is one left in its dock, but can only house one person at time...
echo connect room Escape Pods to Officer Quarters via south
echo connect room Officer Quarters to Escape Pods via north
echo create item Escape Pod Key Card desc A simple key card that appears to activate an escape pod. Will you use it?
echo set item Escape Pod Key Card unique
echo put item Escape Pod Key Card in room Escape Pods


echo create room Brig desc Rows of empty cells fill the brig. All but one. An absolute unit of an Aussie is chained up and unconsious. His sell is labelled MAX. 
echo connect room Brig to Escape Pods via east
echo connect room Escape Pods to Brig via west


echo create room Medical Suite desc The medical suite contains a bed surrounded by smashed monitoring devices. Blood stains the walls and you see the body of a human, dead on the floor. A human? But you are from the last human tribe in the galaxy, how can this be?
echo connect Medical Suite to Escape Pods via west
echo connect Escape Pods to Medical Suite via east
echo create item Note desc You find a bloodied not crumpled in the hand of the dead man. It reads "Deliver Max." What could this mean?
echo set item Note unique
echo put item Note in room Medical Suite


 