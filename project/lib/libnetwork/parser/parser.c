#include "parser.h"

MessageClient clientJsonToStruct(char * json) {
    MessageClient msg = newMessageClient();
    //msg.message = malloc(100 * sizeof(char));
    //msg.user = malloc(10 * sizeof(char));
    //msg.password = malloc(10 * sizeof(char));

    json_scanf(json, strlen(json), "{method: %B}", &(msg.method));
    json_scanf(json, strlen(json), "{sender: %B}", &(msg.sender));
    json_scanf(json, strlen(json), "{group: %B}", &(msg.group));
    json_scanf(json, strlen(json), "{receiver: %B}", &(msg.receiver));

    json_scanf(json, strlen(json), "{message: %Q}", &(msg.message));
    json_scanf(json, strlen(json), "{user: %Q}", &(msg.user));
    json_scanf(json, strlen(json), "{password: %Q}", &(msg.password));

    return msg;
}

MessageServer serverJsonToStruct(char * json) {
    MessageServer msg = newMessageServer();

    json_scanf(json, strlen(json), "{method: %B}", &(msg.method));
    json_scanf(json, strlen(json), "{message: %Q}", &(msg.message));
    json_scanf(json, strlen(json), "{sender: %B}", &(msg.sender));
    json_scanf(json, strlen(json), "{group: %B}", &(msg.group));

    return msg;
}

char * clientStructToJson(MessageClient msg) {
    char * str;
    str = (char *) malloc(200 * sizeof(char));
    // please free the memory after using :>

    struct json_out json = JSON_OUT_BUF(str, 200);
    printf("Method: %d\n", msg.method);
    json_printf(&json, "{method: %d, sender: %d, group: %d, receiver: %d, message: %Q, user: %Q, password: %Q}", msg.method, msg.sender, msg.group, msg.receiver, msg.message, msg.user, msg.password);
    //printf("%s\n", str);
    return str;
}

char * serverStructToJson(MessageServer msg) {
    char * str;
    str = (char *) malloc(200 * sizeof(char));
    struct json_out json = JSON_OUT_BUF(str, 200);
}

json_printf(&json, "{method: %d, message: %Q, error: %M, sender: %d, group: %d}", msg.method, msg.message, msg.error, msg.sender, msg.group);