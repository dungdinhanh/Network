#ifndef _GROUP_H_
#define _GROUP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"
#define MAX_USER_GROUP 100
#define MAX_NAME_GROUP 100

typedef struct Group
{
    char *groupName;
    int groupID;
    User *user;
    int countUser;
}Group;


Group newGroup();

void addUserIntoGroupObject(Group * group, User user);

#endif

