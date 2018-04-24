#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libio/database_api.h>


int main()
{
	startConnection();
	char * query = insertGroupQuery("dad", 1);
	printf("%s\n", query);
	insertGroup("dad", 1);

	closeConnection();
	return 0;
}