#include "parser.h"

MessageClient jsonToStruct(char * json) {
    MessageClient msg;
    msg.message = malloc(100 * sizeof(char));
    msg.user = malloc(10 * sizeof(char));
    msg.password = malloc(10 * sizeof(char));

    json_scanf(json, strlen(json), "{method: %B}", &(msg.method));
    json_scanf(json, strlen(json), "{sender: %B}", &(msg.sender));
    json_scanf(json, strlen(json), "{group: %B}", &(msg.group));
    json_scanf(json, strlen(json), "{receiver: %B}", &(msg.receiver));

    json_scanf(json, strlen(json), "{message: %Q}", &(msg.message));
    json_scanf(json, strlen(json), "{user: %Q}", &(msg.user));
    json_scanf(json, strlen(json), "{password: %Q}", &(msg.password));

    return msg;
}