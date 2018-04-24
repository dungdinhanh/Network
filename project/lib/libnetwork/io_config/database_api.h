#ifndef _DATABASE_API_H_
#define _DATABASE_API_H_

#define SERVER "localhost"
#define USERNAME "group8"
#define PASSWORD "123"
#define DATABASE "ChatProgram"
#include "database.h"
#include <mysql.h>
#include <libent/user.h>

extern MysqlConnector mysqlConnect;
extern MYSQL *databaseConnect;

void startConnection();

void closeConnection();

int checkConnection();

//for users
char *insertUserQuery(char *userName, char *password);

void insertUser(char *userName, char *password);

char *getUserQuery(char *userName, char *password);

User getUser(char *userName, char *password);

// for group
char *insertGroupQuery(char *groupName, int creatorID);

char *getGroupQuery(int groupID);

void insertGroup(char *groupName, int creatorID);

#endif