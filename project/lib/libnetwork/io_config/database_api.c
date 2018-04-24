#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libent/user.h>
#include "database_api.h"
#include "database.h"
#define MAX_LINE_QUERY 1000

MysqlConnector mysqlConnect;
MYSQL *databaseConnect = NULL;

void startConnection(){
	mysqlConnect = newMysqlConnector();
	setHostName(mysqlConnect, SERVER);
	setUserMy(mysqlConnect, USERNAME);
	setPassMy(mysqlConnect, PASSWORD);
	setDatabase(mysqlConnect, DATABASE);
	databaseConnect = connectDatabase(mysqlConnect);
}


void closeConnection(){
	if(databaseConnect == NULL)
		return;
	mysql_close(databaseConnect);
	databaseConnect = NULL;
}


//For users

char *insertUserQuery(char *userName, char *password)
{
	char *query = (char *) malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "INSERT INTO users (user_name, password) VALUES(\"%s\", \"%s\");", userName, password);
	return query;
}

void insertUser(char *userName, char *password)
{
	char *query = insertUserQuery(userName, password);
	getResult(databaseConnect, query);
}

char *getUserQuery(char *userName, char *password)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * FROM users WHERE user_name = \"%s\" AND password = \"%s\";", userName, password);
	return query;
}

User getUser(char *userName, char *password)
{
	User user = newUser();
	char *query = getUserQuery(userName, password);
	MYSQL_RES *res = getResult(databaseConnect, query);
	MYSQL_ROW * row = mysql_fetch_row(res);
	if(row != NULL)
	{		
		setUserName(user, row[1]);
		setPassword(user, row[2]);
		setUserID(user, atoi(row[0]));
	}
	return user;
}



//For Group
char *insertGroupQuery(char *groupName, int creatorID)
{
	char *query = (char *)malloc(sizeof(char) * 1000);
	sprintf(query, "INSERT INTO  groups (group_name, creator_id) VALUES (\"%s\" , %d);", groupName, creatorID);
	return query;
}

char *getGroupQuery(int groupID)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * FROM groups WHERE id = %d", groupID);
	return query;
}

void insertGroup(char *groupName, int creatorID)
{
	char *query = insertGroupQuery(groupName, creatorID);
	getResult(databaseConnect, query);
}


// void getGroup(int group_id)
// {
// 	char *query = getGroupQuery(group_id);
// 	MYSQL_RES *res = getResult(databaseConnect, query);
// 	MYSQL_ROW * row;
// 	// while((row = mysql_fetch_row(res)) != NULL)
// 	// {
// 	// 	printf("%s , %s, %s\n", row[0], row[1], row[2]); // always get string
// 	// }
// }
