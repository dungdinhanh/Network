#include <libconfig/message.h>
#include "frozen.h"


MessageClient clientJsonToStruct(char * json);
MessageServer serverJsonToStruct(char * json);
char * clientStructToJson(MessageClient msg);
char * serverStructToJson(MessageServer msg);


int *parseIntegerArray(char *stringArray);
char * parserArrayToString(int * array);
char * parseObjectArrayToString(Object * array);
void printErrorArray(int * array);
void printResult(int *a);