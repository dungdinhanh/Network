#include <libparse/parser.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX_ARRAY 100


int main() {
    char * str = "{ \"method\": 1, \"message\": \"Hello\", \"user\": \"anhanq\", \"password\": \"anhanqq\", \"sender\": 1, \"group\": 1, \"receiver\": 2, }";
    MessageClient msg = clientJsonToStruct(str);
    printf("Message: %s\n", msg.message);
    printf("User: %s\n", msg.user);
    printf("Password: %s\n", msg.password);
    char * abc = "[1,2, 3, 8 , 5, 6]";
    int * result = parseIntegerArray(abc);
    printResult(result);
    return 0;
} 

