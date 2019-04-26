#include <string>
#include <iostream>
#include <regex>
#include <sstream>
#include "hiredis.h"
#include "item.h"
#include "database.h"
using namespace std;
int main(){
    Database c;
    Item *laser_gun = new Item("Laser gun","Zap those pirates with this dangerous weapon","Ben",(ITEM_TYPE)2);
    laser_gun->save(-2);
    delete laser_gun;
    Item *ID2=c.read_lastid(-2);
    return 0;
}
