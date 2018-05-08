#include <libconfig/message.h>
#include "frozen.h"

MessageClient clientJsonToStruct(char * json);
MessageServer serverJsonToStruct(char * json);
char * clientStructToJson(MessageClient msg);
char * serverStructToJson(MessageServer msg);
int *parseIntegerArray(char *stringArray);

void printResult(int *a);