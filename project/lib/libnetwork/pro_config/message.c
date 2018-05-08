#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"

//--------------------------------------
//initialization
MessageClient newMessageClient() // init message client
{
  MessageClient messageClient;
  messageClient.method = D_INT;
  
  messageClient.message = (char *)malloc(sizeof(char) * MAX_LINE);
  strcpy(messageClient.message, D_STRING);
  
  messageClient.user = (char *)malloc(sizeof(char) * MAX_OBJECT);
  strcpy(messageClient.user, D_STRING);
  
  messageClient.password = (char *)malloc(sizeof(char) * MAX_OBJECT);
  strcpy(messageClient.password, D_STRING);
  
  messageClient.sender = D_INT;
  messageClient.group = D_INT;
  messageClient.receiver = D_INT;
  return messageClient;
}

Object initObject()
{
  Object object;
  object.id = D_INT;
  object.user = (char *)malloc(sizeof(char) * MAX_OBJECT);
  return object;
}

MessageServer newMessageServer()
{
  MessageServer messageServer;
  messageServer.method = D_INT;

  messageServer.message = (char *)malloc(sizeof(char) * MAX_LINE);
  strcpy(messageServer.message, D_STRING);

  messageServer.senderName = (char *)malloc(sizeof(char) * MAX_LINE);
  strcpy(messageServer.senderName, D_STRING);

  messageServer.sender = D_INT;
  messageServer.code = D_INT;
  messageServer.sender = D_INT;
  messageServer.receiver = D_INT;
  int i;

  for(i = 0; i< MAX_ERROR; i++)
  {
    messageServer.error[i] = D_INT;
  }

  messageServer.object = (Object *)malloc(sizeof(Object) * MAX_OBJECT);
  for(i = 0; i< MAX_OBJECT; i++)
  {
    messageServer.object[i] = initObject();
  }

  messageServer.currentObject = 0;
  messageServer.currentError = 0;
  return messageServer;
}


// Getter Setter of Client
void setMethodClient(MessageClient messageClient, int method){
  messageClient.method = method;
  // printf("method pass : %d", method);
  // printf("method out: %d\n", messageClient.method);
}

int getMethodClient(MessageClient messageClient){
  return messageClient.method;
}
//------------------


void setMessageClient(MessageClient messageClient, char *message){
  strcpy(messageClient.message, message);
}

char *getMessageClient(MessageClient messageClient){
  return messageClient.message;
}
//------------------


void setUserClient(MessageClient messageClient, char *user){
  strcpy(messageClient.user, user);
}

char *getUserClient(MessageClient messageClient){
  return messageClient.user;
}
//-------------------


void setPasswordClient(MessageClient messageClient, char *password){
  strcpy(messageClient.password, password);
}

char *getPasswordClient(MessageClient messageClient){
  return messageClient.password;
}

//-------------------
void setSenderClient(MessageClient messageClient, int sender){
  messageClient.sender = sender;
}

int getSenderClient(MessageClient messageClient){
  return messageClient.sender;
}
//--------------------

void setGroupClient(MessageClient messageClient, int group){
  messageClient.group = group;
}

int getGroupClient(MessageClient messageClient){
  return messageClient.group;
}
//--------------------------

void setReceiverClient(MessageClient messageClient, int receiver){
  messageClient.receiver = receiver;
}

int getReceiverClient(MessageClient messageClient){
  return messageClient.receiver;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//Getter and Setter of server
int getMethodServer(MessageServer messageServer)
{
  return messageServer.method;
}


void setMethodServer(MessageServer messageServer, int method)
{
  messageServer.method = method;
}
//------------------------

char *getMessageServer(MessageServer messageServer)
{
  return messageServer.message; 
}

void setMessageServer(MessageServer messageServer, char *message)
{
  strcpy (messageServer.message, message);
}
//-------------------------------------------
void setCodeServer(MessageServer messageServer, int code)
{
  messageServer.code = code;
}

int getCodeServer(MessageServer messageServer)
{
  return messageServer.code;
}

//------------------------

void setSenderNameServer(MessageServer messageServer, char *senderName)
{
  strcpy(messageServer.senderName, senderName);
}

char *getSenderNameServer(MessageServer messageServer)
{
  return messageServer.senderName;
}
//--------------------------
void setSenderServer(MessageServer messageServer, int sender)
{
  messageServer.sender = sender;
}

int getSenderServer(MessageServer messageServer)
{
  return messageServer.sender;
}
//-----------------------------
void setReceiverServer(MessageServer messageServer, int receiver)
{
  messageServer.receiver = receiver;
}

int getReceiverServer(MessageServer messageServer)
{
  return messageServer.receiver;
}

//-------------------------
void addError(MessageServer messageServer, int error)
{
  messageServer.currentError += 1;
  messageServer.error[messageServer.currentError - 1] = error;
}

int getError(MessageServer messageServer, int index)
{
  if(index >= messageServer.currentError)
  {
    return messageServer.error[index];
  }
  else return -1;
}
//-------------------------
void setGroupServer(MessageServer messageServer, int group)
{
  messageServer.group = group;
}

int getGroupServer(MessageServer messageServer)
{
  return messageServer.group;
}
//--------------------------
void addObject(MessageServer message, Object object)
{
  message.currentObject += 1;
  message.object[message.currentObject - 1] = object;
}

Object getObject(MessageServer message, int index)
{
  if(index >= message.currentObject)
  {
    return message.object[index];
  }
  return initObject();
}
//---------------------------------------------------------------
//---------------------------------------------------------------
//Object init
void setIDObject(Object object, int id)
{
  object.id = id;
}

int getIDObject(Object object)
{
  return object.id;
}

//-------------------------------------
void setUserObject(Object object, char *user)
{
  strcpy(object.user, user);
}

char *getUserObject(Object object)
{
  return object.user;
}

void setObject(Object object, int id ,char *user)
{
  object.id = id;
  strcpy(object.user, user);
}
//------------------------------------