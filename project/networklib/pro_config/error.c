#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define ERROR_NUMBER 5;

typedef struct Error{
	ErrorCode errorCode;
	char *message;
}Error;


Error error[ERROR_NUMBER] ={
	{ZERO_ERROR, "Zero Error"}
	{EXIST_USER, "User exists in database"},
	{TOO_LONG_USER, "User name is too long, length must be less or equal 16"},
	{TOO_SHORT_PASSWORD, "Password is not secured, length must be at least 6"},
	{WRONG_USER_PASSWORD, "Wrong user or Password"},
	{CONNECTION_ERROR, "Connection has Error"}
}

char *getErrorMessage(ErrorCode errorCode){
	int i;
	for (int i = 0; i < ERROR_NUMBER; i++)
	{
		/* code */
		if(errorCode == i)
			return error[i].message;
	}
}

int main()
{
	printf("%s\n", getErrorMessage(1));
	return 0;
}