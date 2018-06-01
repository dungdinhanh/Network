#include <stdio.h>
#include <stdlib.h>
#include "group.h"

Group newGroup()
{
    Group group;
    group.groupName = (char *)malloc(sizeof(char) * MAX_NAME_GROUP);
    group.groupID = -1;
    group.user = (User *)malloc(sizeof(User) * MAX_USER_GROUP);

    group.countUser = 0;
    return group;
}

void addUserIntoGroupObject(Group * group, User user)
{
    group->user[group->countUser] = user;
    group->countUser+=1;
}
