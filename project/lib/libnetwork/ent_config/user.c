#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"


//Construct
User newUser() //create user has empty username + password id = -1
{
	User user;
	user.userName = (char *)malloc(sizeof(char) * USER_LENGTH);
	user.password = (char *)malloc(sizeof(char) * USER_LENGTH);
	user.id = -1;
	return user;
}


//Getter

char *getUserName(User user)
{
	return user.userName;
}

char *getPassword(User user)
{
	return user.password;
}


int getUserID(User user)
{
	return user.id;
}


//Setter

void setUserName(User user, char *userName)
{
	if(userName == NULL)return;

	strcpy(user.userName, userName);
}


void setPassword(User user, char *password)
{
	if(password == NULL)return;
	strcpy(user.password, password);
}

void setUserID(User user, int id)
{
	user.id = id;
}