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


MysqlConnector newMysqlConnector();

void setHostName(MysqlConnector mysqlConnector,char *hostName);


void setUserMy(MysqlConnector mysqlConnector, char *userName);

void setPassMy(MysqlConnector mysqlConnector, char *password);

void setDatabase(MysqlConnector mysqlConnector, char *database);

char *getHostName(MysqlConnector mysqlConnector);

char *getUserMy(MysqlConnector mysqlConnector);

char *getPassMy(MysqlConnector mysqlConnector);

char *getDatabase(MysqlConnector mysqlConnector);


MYSQL *connectDatabase(MysqlConnector mysqlConnector);


MYSQL_RES *getResult(MYSQL *conn, char *query);

#endif