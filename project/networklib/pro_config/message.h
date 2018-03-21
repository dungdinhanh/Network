#ifndef __MESSAGE_H__
#define __MESSAGE_H__


#define MAX_LINE 4096
#define MAX_ERROR 20
#define MAX_OBJECT 2000
#define D_INT -1
#define D_STRING ""

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
}

typedef struct MessageServer{
  int method;
  char *message;
  int error[MAX_ERROR];
  int sender;
  int group;
  Object *object;
  //below will not be wrapped in json
  int currentObject;
  int currentError;
}MessageServer;

//init
MessageClient newMessageClient();
MessageServer newMessageServer();
Object initObject();
int checkNull(Object object);

//getter setter Client

void setMethodClient(MessageClient messageClient, int method);

int getMethodClient(MessageClient messageClient);

void setMessageClient(MessageClient messageClient, char *message);

char *getMessageClient(MessageClient messageClient);

void setUserClient(MessageClient messageClient, char *user);

char *getUserClient(MessageClient messageClient);

void setPasswordClient(MessageClient messageClient, char *password);

char *getPasswordClient(MessageClient messageClient);

void setSenderClient(MessageClient messageClient, int sender);

int getSenderClient(MessageClient messageClient);

void setGroupClient(MessageClient, int group);

int getGroupClient(MessageClient messageClient);

void setReceiverClient(MessageClient messageClient, int receiver);

int getReceiverClient(MessageClient messageClient);


//getter setter Server

void setMethodServer(MessageServer messageServer, int method);

int getMethodServer(MessageServer messageServer);

void setMessageServer(MessageServer messageServer, char *message);

char *getMessageServer(MessageServer messageServer);

void addError(MessageServer messageServer, int error);

int getError(MessageServer messageServer, int index);

void setGroupServer(MessageServer messageServer, int group);

int getGroupServer(MessageServer messageServer);

void addObject(MessageServer messageServer, Object object);

Object getObject(MessageServer messageServer, int index);

#endif
