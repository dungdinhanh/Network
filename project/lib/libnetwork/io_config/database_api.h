#ifndef _DATABASE_API_H_
#define _DATABASE_API_H_

#define SERVER "localhost"
#define USERNAME "group8"
#define PASSWORD "123"
#define DATABASE "ChatProgram"
#include "database.h"
#include <mysql.h>

extern MysqlConnector mysqlConnect;
extern MYSQL *databaseConnect;

void startConnection();

void closeConnection();


char *insertGroupQuery(char *groupName, int creatorID);

char *getGroupQuery(int groupID);

void insertGroup(char *groupName, int creatorID);

#endif