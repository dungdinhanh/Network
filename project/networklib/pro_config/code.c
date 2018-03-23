#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"
#define MAX_CODE 13

typedef struct Code{
	CodeNum codeNum;
	char *message;
}Code;

Code code[MAX_CODE] = {
	{ZERO_CODE, "No code"},
	{SUCCESS_LOGIN, "Log in successfully"},
	{SUCCESS_LOGOUT, "Log out successfully"},
	{SUCCESS_CREATE_ACCOUNT, "Create account successfully"},
	{SUCCESS_CREATE_GROUP, "Create group successfully"},
	{SUCCESS_ADD_USER, "add user to group successfully"},
	{SUCCESS_SEND_MESSAGE, "send message successfully"},
	{FAIL_LOGIN, "Fail to Log in"},
	{FAIL_LOGOUT, "Fail to log out"},
	{FAIL_CREATE_ACCOUNT, "Fail to create account"},
	{FAIL_CREATE_GROUP, "Fail to create group"},
	{FAIL_ADD_USER, "Fail to add user to group"},
	{FAIL_SEND_MESSAGE, "Fail to send message"}
};


char *getCodeMessage(CodeNum codeNum){
	int i;
	if(codeNum >= MAX_CODE){
		printf("Not a server message");
		return "\0";
	}
	return code[codeNum].message;
}

// int main(){
// 	printf("%s\n", getCodeMessage(0));
// 	printf("%s\n", getCodeMessage(1));
// 	printf("%s\n", getCodeMessage(2));
// 	printf("%s\n", getCodeMessage(3));
// 	printf("%s\n", getCodeMessage(4));
// 	printf("%s\n", getCodeMessage(5));
// 	printf("%s\n", getCodeMessage(7));
// 	printf("%s\n", getCodeMessage(8));
// 	printf("%s\n", getCodeMessage(9));
// 	printf("%s\n", getCodeMessage(10));
// 	printf("%s\n", getCodeMessage(11));
// 	printf("%s\n", getCodeMessage(12));
// 	printf("%s\n", getCodeMessage(13));
// 	printf("%s\n", getCodeMessage(14));
// 	return 0;
// }