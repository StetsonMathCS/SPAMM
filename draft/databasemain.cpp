#include <string>
#include "hiredis.h"
#include "redisdemo.h"
using namespace std;
int main(){

    RedisDemo c;
    string s = "key";
    string v = "val";
    c.write(s,v);
    c.read(s);
    return 0;
}
