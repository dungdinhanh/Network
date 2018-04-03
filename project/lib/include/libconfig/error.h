#ifndef __ERROR_H_
#define __ERROR_H_

typedef enum 
{
	ZERO_ERROR,
	EXIST_USER,
	TOO_LONG_USER,
	TOO_SHORT_PASSWORD,
	WRONG_USER_PASSWORD,
	CONNECTION_ERROR
}ErrorCode;

char *getErrorMessage(ErrorCode errorCode);

#endif