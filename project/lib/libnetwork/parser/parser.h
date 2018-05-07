//#include <libconfig/message.h>
#include "frozen.h"
#include "frozen.c"

typedef struct MessageClient{
  int method;
  char *message;
  char *user;
  char *password;
  int sender;
  int group;
  int receiver;
} MessageClient;

typedef struct Object{
  int id;
  char *user;
}Object;

typedef struct MessageServer{
  int method;
  char *message;
  int error[20];
  int sender;
  int group;
  Object *object;
  //below will not be wrapped in json
  int currentObject;
  int currentError;
}MessageServer;

MessageClient newMessageClient();
MessageServer newMessageServer();
MessageClient clientJsonToStruct(char * json);
MessageServer serverJsonToStruct(char * json);
char * clientStructToJson(MessageClient msg);
char * serverStructToJson(MessageServer msg);