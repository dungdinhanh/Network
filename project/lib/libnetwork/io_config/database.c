#include "database.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <my_global.h>


MysqlConnector MysqlConnector(){
	MysqlConnector mysqlConnector;
	mysqlConnector.hostName = (char *)malloc(sizeof(char) * MAX_NAME);
	mysqlConnector.userName = (char *)malloc(sizeof(char) * MAX_NAME);
	mysqlConnector.password = (char *)malloc(sizeof(char) * MAX_NAME);
	mysqlConnector.database = (char *)malloc(sizeof(char) * MAX_NAME);
	return mysqlConnector;
}

void setHostName(MysqlConnector mysqlConnector,char *hostName){
	strcpy(mysqlConnector.hostName, hostName);
}


void setUserName(MysqlConnector mysqlConnector, char *userName){
	strcpy(mysqlConnector.userName, userName);
}

void setPassword(MysqlConnector mysqlConnector, char *password){
	strcpy(mysqlConnector.password, password);
}

void setDatabase(MysqlConnector mysqlConnector, char *database){
	strcpy(mysqlConnector.database, database);
}


char *getHostName(MysqlConnector mysqlConnector){
	return mysqlConnector.hostName;
}

char *getUserName(MysqlConnector mysqlConnector){
	return mysqlConnector.userName;
}


char *getPassword(MysqlConnector mysqlConnector){
	return mysqlConnector.password;
}

char *getDatabase(MysqlConnector mysqlConnector){
	return mysqlConnector.database;
}

int equal(MysqlConnector mysqlConnector, MysqlConnector mysqlConnector1){
	if(!strcmp(mysqlConnector.hostName, mysqlConnector1.hostName))
	{
		return 0;
	}
	else if(!strcmp(mysqlConnector.userName, mysqlConnector1.userName))
	{
		return 0;
	}
	else if(!strcmp(mysqlConnector.password, mysqlConnector1.password))
	{
		return 0;
	}
	else if(!strcmp(mysqlConnector.database, mysqlConnector1.database)){
		return 0;
	}
	else return 1;
}


