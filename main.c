#include "class.h"

int main()
{
    pUser user = newUser("mike", 26, 178.4, 72.6);
    user->printUserInfo();
    free(user);
}

/*
output :

-------[user info]-------
  name   : mike
  age    : 26
  height : 178.40(cm)
  weight : 72.60(kg)
-------------------------
*/
