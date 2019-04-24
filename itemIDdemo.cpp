#include "item.h"
#include "database.h"


int main(){

Database d = new Database();

Item a = new Item("Name","Description");

a.save();

delete d;
delte a;

return 0;

}

