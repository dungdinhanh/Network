#include <libconfig/message.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "frozen.h"
#include "parser.h"
#define MAX_ARRAY 100

MessageClient clientJsonToStruct(char * json) {
    //MessageClient msg = newMessageClient();
    MessageClient msg;
    msg.message = (char *) malloc(100 * sizeof(char));
    msg.user = (char *) malloc(10 * sizeof(char));
    msg.password = (char *) malloc(10 * sizeof(char));

    json_scanf(json, strlen(json), "{method: %d}", &(msg.method));
    json_scanf(json, strlen(json), "{sender: %d}", &(msg.sender));
    json_scanf(json, strlen(json), "{group: %d}", &(msg.group));
    json_scanf(json, strlen(json), "{receiver: %d}", &(msg.receiver));

    json_scanf(json, strlen(json), "{message: %Q}", &(msg.message));
    json_scanf(json, strlen(json), "{user: %Q}", &(msg.user));
    json_scanf(json, strlen(json), "{password: %Q}", &(msg.password));
    return msg;
}

char * clientStructToJson(MessageClient msg) {
    char * str;
    str = (char *) malloc(200 * sizeof(char));

    struct json_out json = JSON_OUT_BUF(str, 200);
    json_printf(&json, "{method: %d, sender: %d, group: %d, receiver: %d, message: %Q, user: %Q, password: %Q}", msg.method, msg.sender, msg.group, msg.receiver, msg.message, msg.user, msg.password);
    return str;
}

MessageServer serverJsonToStruct(char * json) {
    MessageServer msg;
    
    msg.message = (char *) malloc(100 * sizeof(char));
    
    json_scanf(json, strlen(json), "{method: %d}", &(msg.method));
    json_scanf(json, strlen(json), "{sender: %d}", &(msg.sender));
    json_scanf(json, strlen(json), "{group: %d}", &(msg.group));
    json_scanf(json, strlen(json), "{message: %Q}", &(msg.message));

    // parse error array
    char * error = (char *) malloc(100 * sizeof(char));
    int * errorArray = (int *) malloc(100 * sizeof(int));
    json_scanf(json, strlen(json), "{error: %Q}", &error);
    errorArray = parseIntegerArray(error);

    int i = 0;
    while (errorArray[i]) {
        msg.error[i] = errorArray[i];
        i++;
    }
    free(error);
    free(errorArray);

    // parse object array
    msg.object = malloc(10 * sizeof(Object));
    struct json_token t;
    for (i = 0; json_scanf_array_elem(json, strlen(json), ".object", i, &t) > 0; i++) {
        msg.object[i].user = (char *) malloc(100 * sizeof(char)); 
        json_scanf(t.ptr, t.len, "{id: %d, user: %Q}", &msg.object[i].id, &msg.object[i].user);
        printf("Id: %d\n", msg.object[i].id);
        printf("User: %s\n", msg.object[i].user);
    }
    return msg;
}

char * serverStructToJson(MessageServer msg) {
    char * str;
    str = (char *) malloc(200 * sizeof(char));
    struct json_out json = JSON_OUT_BUF(str, 200);
    return str;
}


int *parseIntegerArray(char *stringArray) {
    int * result = (int *)malloc(sizeof(int) * MAX_ARRAY);
    char *s = "[,\n ";
    char *tempString = (char *)malloc(sizeof(char) * MAX_ARRAY);
    strcpy(tempString, stringArray);
    char * buffer = (char *)malloc(sizeof(char) * MAX_ARRAY);
    int count = 0;
    buffer = strtok(tempString, s);
    while(1) {
        int element = atoi(buffer);
        result[count] = element;
        count++;
        if((buffer= strtok(NULL, s)) == NULL)
            break;
    }
    result[count] = -1;
    return result;
}


void printResult(int *a) {
    if (a == NULL)
        return;
    int i = 0;
    while(a[i] != -1) {
        printf("%d  ", a[i]);
        i++;
    }
    printf("\n");
}