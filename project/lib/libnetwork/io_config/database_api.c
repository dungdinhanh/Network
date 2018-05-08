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
	if(databaseConnect != NULL)return;
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

int checkConnection()
{
	if(databaseConnect == NULL)return 0;
	else return 1;
}


//For users

char *insertUserQuery(char *userName, char *password)
{
	char *query = (char *) malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "INSERT INTO users (user_name, password) VALUES(\"%s\", \"%s\");", userName, password);
	return query;
}

int insertUser(char *userName, char *password)
{
	char *query = insertUserQuery(userName, password);
	if(getResult(databaseConnect, query) != NULL)return 1;
	else return 0;
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
		user.id = atoi(row[0]);
		//setUserID(user, atoi(row[0]));
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

int insertGroup(char *groupName, int creatorID)
{
	char *query = insertGroupQuery(groupName, creatorID);
	if(getResult(databaseConnect, query) != NULL) return 1;
	else return 0;
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


//for adding users to group
char *addUserToGroupQuery(int userID, int groupID)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "INSERT INTO user_group VALUES ( %d , %d );", userID, groupID);
	return query;
}

int addUserToGroup(int userID, int groupID)
{
	char *query = addUserToGroupQuery(userID, groupID);
	if(getResult(databaseConnect, query) != NULL) return 1;
	else return 0;
}

char *getUsersFromGroupQuery(int groupID)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * FROM user_group WHERE group_id = %d ;", groupID);
	return query;
}


int *getUsersFromGroup(int groupID)
{
	int * userIDs = (int *)malloc(sizeof(int) * MAX_LINE_QUERY);
	char *query = getUsersFromGroupQuery(groupID);
	MYSQL_RES * res;
	int count = 0;
	if (res = getResult(databaseConnect, query) != NULL)
	{
		MYSQL_ROW * row;
		while((row = mysql_fetch_row(res)) != NULL)
		{
			userIDs[count] = atoi(row[0]);
			count++;
		}
		return userIDs;
	}
	else return NULL;
}