#include <string>
#include "hiredis.h"
#include "redisdemo.h"
#include "dict.h"
using namespace std;
int main(){


    Database c;
    string s = "key";
    string v = "val";
    c.write(s,v);
    c.read(s);
    
    return 0;

}
