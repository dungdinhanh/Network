#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libio/database_api.h>
#include <libent/user.h>

// test create group
// int main()
// {
// 	startConnection();
// 	char * query = insertGroupQuery("dad", 1);
// 	printf("%s\n", query);
// 	insertGroup("dad", 1);

// 	closeConnection();
// 	return 0;
// }


//test insert user
// int main()
// {
// 	startConnection();
// 	char *query = insertUserQuery("dungdinhanh", "12345678");
// 	printf("%s\n", query);
// 	insertUser("dungdinhanh", "12345678");
// 	closeConnection();
// 	return 0;
// }

//test get user successful
// int main()
// {
// 	startConnection();
// 	char *query = getUserQuery("dungdinhanh", "12345678");
// 	printf("%s\n", query);
// 	User user = getUser("dungdinhanh", "12345678");
// 	printf("user name: %s\n" , user.userName);
// 	printf("password : %s\n", user.password);;
// 	closeConnection();
// 	return 0;
// }



//test get user fail
int main()
{
	startConnection();
	char *query = getUserQuery("dungdinhanh1", "12345678");
	printf("%s\n", query);
	User user = getUser("dungdinhanh1", "12345678");
	if(user.id == -1)
	{
		printf("Log in fail\n");
	}
	else
	{
		printf("user name: %s\n", user.userName);
		printf("password : %s\n", user.password);
	}
	return 0;

}


//test check connection
// int main()
// {
// 	printf(" check connection = %d\n", checkConnection());
// 	startConnection();
// 	printf("check connection after connection = %d\n", checkConnection());
// 	closeConnection();
// 	printf("check connection after close connection = %d\n", checkConnection());
// }