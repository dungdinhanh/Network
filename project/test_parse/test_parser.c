#include <libparse/parser.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_ARRAY 100


int main() {
    // char * str = "{ \"method\": 1, \"message\": \"Hello\", \"user\": \"anhanq\", \"password\": \"anhanqq\", \"sender\": 1, \"group\": 1, \"receiver\": 2, }";
    // MessageClient msg = clientJsonToStruct(str);
    // printf("Message: %s\n", msg.message);
    // printf("User: %s\n", msg.user);
    // printf("Password: %s\n", msg.password);
    
    char * serverMsg = "{\"method\": 10, \"message\": \"Hello from server\", \"error\": [1, 2, 3, 4, 5, -1], \"sender\": 10, \"group\": 1, \"object\": [{\"id\": 1, \"user\": \"anhanq\"}, {\"id\": 2, \"user\": \"dungda\"}, {\"id\": -1, \"user\": \"\"}]}";
    MessageServer x = serverJsonToStruct(serverMsg);
    //printf("Message: %s\n", x.message);
    //printResult(x.error);
    serverStructToJson(x);
    //parserArrayToString(x.error);
    //printResult(parseIntegerArray(parserArrayToString(x.error)));
    x = serverJsonToStruct(serverMsg);
    //printf("Message: %s\n", x.message);
    //printResult(x.error);
    //parseObjectArrayToString(x.object);

    return 0;
} 

