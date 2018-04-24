#include "database.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <my_global.h>


MysqlConnector newMysqlConnector(){
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


void setUserMy(MysqlConnector mysqlConnector, char *userName){
	strcpy(mysqlConnector.userName, userName);
}

void setPassMy(MysqlConnector mysqlConnector, char *password){
	strcpy(mysqlConnector.password, password);
}

void setDatabase(MysqlConnector mysqlConnector, char *database){
	strcpy(mysqlConnector.database, database);
}


char *getHostName(MysqlConnector mysqlConnector){
	return mysqlConnector.hostName;
}

char *getUserMy(MysqlConnector mysqlConnector){
	return mysqlConnector.userName;
}


char *getPassMy(MysqlConnector mysqlConnector){
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


MYSQL *connectDatabase(MysqlConnector mysqlConnector)
{
	MYSQL *conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, getHostName(mysqlConnector), getUserMy(mysqlConnector), 
		getPassMy(mysqlConnector), getDatabase(mysqlConnector),0, NULL, 0))
	{
		printf("%s\n", mysql_error(conn));
		exit(1);
	}
	return conn;
}


MYSQL_RES *getResult(MYSQL *conn, char *query)
{
	MYSQL_RES * res;
	if(mysql_query(conn, query))
	{
		printf("%s\n", mysql_error(conn));
		return NULL;
	}
	res = mysql_use_result(conn);
	return res;
}






// int main(){

// 	MysqlConnector mysqlConnector = newMysqlConnector();
// 	setHostName(mysqlConnector, "localhost");
// 	setUserName(mysqlConnector, "group8");
// 	setDatabase(mysqlConnector, "ChatProgram");
// 	setPassword(mysqlConnector, "123");

// 	MYSQL *conn = connectDatabase(mysqlConnector);
// 	MYSQL_RES *res = getResult(conn, "SELECT * FROM groups");
// 	return 0;
// }
