#include <stdio.h>
#include <stdlib.h>
#include "error.h"

#define ERROR_NUMBER 6

typedef struct Error{
	ErrorCode errorCode;
	char *message;
}Error;


Error error[ERROR_NUMBER] ={
	{ZERO_ERROR, "Zero Error"},
	{EXIST_USER, "User exists in database"},
	{TOO_LONG_USER, "User name is too long, length must be less or equal 16"},
	{TOO_SHORT_PASSWORD, "Password is not secured, length must be at least 6"},
	{WRONG_USER_PASSWORD, "Wrong user or Password"},
	{CONNECTION_ERROR, "Connection has Error"}
};

char *getErrorMessage(ErrorCode errorCode){
	int i;
	if(errorCode >= ERROR_NUMBER){
		printf("Not an error\n");
		return "\0";
	}
	for (int i = 0; i < ERROR_NUMBER; i++)
	{
		/* code */
		if(errorCode == i)
			return error[i].message;
	}
}

// int main()
// {
// 	printf("%s\n", getErrorMessage(1));
// 	printf("%s\n", getErrorMessage(2));
// 	printf("%s\n", getErrorMessage(3));
// 	printf("%s\n", getErrorMessage(4));
// 	printf("%s\n", getErrorMessage(5));
// 	printf("%s", getErrorMessage(6));
// 	return 0;
// }