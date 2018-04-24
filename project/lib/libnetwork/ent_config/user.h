#ifndef _USER_H_
#define _USER_H_
#define USER_LENGTH 100

typedef struct User{
	char *userName;
	char *password;
	int id;
}User;

//Construct
User newUser(); //create user has empty username + password id = -1

//Getter

char *getUserName(User user);

char *getPassword(User user);

int getUserID(User user);



//Setter

void setUserName(User user, char *userName);


void setPassword(User user, char *password);

void setUserID(User user, int id);


#endif