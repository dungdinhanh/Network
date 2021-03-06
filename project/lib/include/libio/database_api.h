#ifndef _DATABASE_API_H_
#define _DATABASE_API_H_

#define SERVER "localhost"
#define USERNAME "group8"
#define PASSWORD "123"
#define DATABASE "ChatProgram"
#include "database.h"
#include <mysql.h>
#include <libent/user.h>
#include <libent/group.h>

extern MysqlConnector mysqlConnect;
extern MYSQL *databaseConnect;

void startConnection();

void closeConnection();

int checkConnection();

//for users
char *insertUserQuery(char *userName, char *password);

int insertUser(char *userName, char *password);

char *getUserQuery(char *userName, char *password);

User getUser(char *userName, char *password);

char *getAllUsersQuery();

User *getAllUsers();


// for group
char *insertGroupQuery(char *groupName, int creatorID);

char *getGroupQuery(int groupID);

int insertGroup(char *groupName, int creatorID);


char *getUserByIDQuery(int id);

User getUserByID(int id); //testing



char *getAllGroupsQuery();

Group *getAllGroups();




// for adding users to group
char *addUserToGroupQuery(int userID, int groupID);

int addUserToGroup(int userID, int groupID);

char *getUsersFromGroupQuery(int groupID);

int *getUsersFromGroup(int groupID);

char *getGroupsForUsersQuery(int user);

int *getGroupsForUsers(int user);


#endif