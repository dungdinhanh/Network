#ifndef __DATABASE_H_
#define __DATABASE_H_
#define MAX_SQL 200
#define MAX_NAME 100
#include <mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct MysqlConnector{
	char *hostName;
	char *userName;
	char *password;
	char *database;
}MysqlConnector;


MysqlConnector MysqlConnector();

void setHostName(MysqlConnector mysqlConnector,char *hostName);


void setUserName(MysqlConnector mysqlConnector, char *userName);

void setPassword(MysqlConnector mysqlConnector, char *password);

void setDatabase(MysqlConnector mysqlConnector, char *database);

char *getHostName(MysqlConnector mysqlConnector);

char *getUserName(MysqlConnector mysqlConnector);

char *getPassword(MysqlConnector mysqlConnector);

char *getDatabase(MysqlConnector mysqlConnector);

#endif