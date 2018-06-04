#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libent/user.h>
#include <libent/group.h>
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
	MYSQL_RES * res;
	char *query = insertUserQuery(userName, password);
	if((res = getResult(databaseConnect, query)) != NULL){
		mysql_free_result(res);
		return 1;
	}
	else
	{
		mysql_free_result(res);
		return 0;
	}
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
	mysql_free_result(res);
	return user;
}

char *getAllUsersQuery()
{
  char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);

  sprintf(query, "SELECT * FROM users");
  return query;
}


User *getAllUsers()
{
  User *user = (User *)malloc(sizeof(User) * 100);
  char *query = getAllUsersQuery();
  MYSQL_RES *res = getResult(databaseConnect, query);
  //MYSQL_ROW *row = mysql_fetch_row(res);
  MYSQL_ROW *row;
  int count = 0;
  while((row = mysql_fetch_row(res)))
  {
	user[count] = newUser();
	user[count].id = atoi(row[0]);
	setUserName(user[count], row[1]);
	setPassword(user[count], row[2]);
	count++;
  }
  user[count] = newUser();
  mysql_free_result(res);
  return user;
}


char *getUserByIDQuery(int id)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * from users where id = %d", id);
	return query;
}

User getUserByID(int id)
{
	User user = newUser();
	char *query = getUserByIDQuery(id);
	MYSQL_RES *res = getResult(databaseConnect, query);
 
  	MYSQL_ROW *row = mysql_fetch_row(res);
	if(row)
	{
		user.id = atoi(row[0]);
		strcpy(user.userName, (char*)row[1]); //char * test 
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
	MYSQL_RES * res;
	if((res = getResult(databaseConnect, query)) != NULL)
	{
		mysql_free_result(res);
		return 1;
	}
	else
	{
		mysql_free_result(res);
		return 0;
	} 
}

char *getAllGroupsQuery()
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * FROM groups");
	return query;
}

Group *getAllGroups()
{
	Group * group = (Group *)malloc(sizeof(Group) * MAX_SQL);
	char *query = getAllGroupsQuery();
	MYSQL_RES *res;
	int count = 0;
	if((res = getResult(databaseConnect, query)) != NULL)
	{
		MYSQL_ROW * row;
		while((row = mysql_fetch_row(res)) != NULL)
		{
			group[count] = newGroup();
			group[count].groupID = atoi((char *)row[0]);
			strcpy(group[count].groupName, row[1]);
			//group[count].user = getUsersFromGroup(group[count].groupID);
			count++;			
		}
		group[count] = newGroup();
		free(row);
		mysql_free_result(res);
		count = 0;
		while(1)
		{
			//printf("in loop2\n");
			if(group[count].groupID == -1)break;
			group[count].user = getUsersFromGroup(group[count].groupID);
			count++;
		}
	}
	else mysql_free_result(res);
	return group;
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
	MYSQL_RES * res;
	if((res = getResult(databaseConnect, query)) != NULL){
		mysql_free_result(res);
		return 1;
	} 
	else{

		mysql_free_result(res);
		return 1;
	};
}

char *getUsersFromGroupQuery(int groupID)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * FROM user_group WHERE group_id = %d ;", groupID);
	return query;
}


int *getUsersFromGroup(int groupID)
{
	int *user = (int *) malloc(sizeof(int) * MAX_LINE_QUERY);
	// int * userIDs = (int *)malloc(sizeof(int) * MAX_LINE_QUERY);
	char *query = getUsersFromGroupQuery(groupID);
	MYSQL_RES * res;
	int count = 0;
	if ((res = getResult(databaseConnect, query)) != NULL)
	{
		// printf("inside loop4\n");
		MYSQL_ROW * row;
		while((row = mysql_fetch_row(res)) != NULL)
		{
			//printf("inside loop5\n");
			user[count] = atoi(row[0]);
			count++;
		}
		user[count] = -1;
		mysql_free_result(res);
		return user;
	}
	else{
		mysql_free_result(res);
		user[0] = -1;
		return user;
	}
}


char *getGroupsForUsersQuery(int user)
{
	char *query = (char *)malloc(sizeof(char) * MAX_LINE_QUERY);
	sprintf(query, "SELECT * FROM user_group WHERE user_id = %d", user);
	return query;
}


int *getGroupsForUsers(int user)
{
	int *group = (int *)malloc(sizeof(char) * 100);
	MYSQL_RES * res;
	int count = 0;
	res = getResult(databaseConnect, getGroupsForUsersQuery(user));
	MYSQL_ROW row;
	while((row = mysql_fetch_row(res)))
	{
		//printf("\ncount in database api : %d\n", count);
		group[count] = atoi(row[1]);
		count++;
	}
	group[count] = -1;
	return group;
}




// User *getUsersFromGroup(int groupID)
// {
// 	User *user = (User *) malloc(sizeof(User) * MAX_LINE_QUERY);
// 	// int * userIDs = (int *)malloc(sizeof(int) * MAX_LINE_QUERY);
// 	char *query = getUsersFromGroupQuery(groupID);
// 	MYSQL_RES * res;
// 	int count = 0;
// 	int userIDTemp;
// 	if (res = getResult(databaseConnect, query) != NULL)
// 	{
// 		MYSQL_ROW * row;
// 		while((row = mysql_fetch_row(res)) != NULL)
// 		{
// 			userIDTemp = atoi((char*)row[0]);
// 			user[count] = getUserByID(userIDTemp);
// 			count++;
// 		}
// 		user[count] = newUser();
// 		mysql_free_result(res);
// 		return user;
// 	}
// 	else{
// 		mysql_free_result(res);
// 		return NULL;
// 	}
// }