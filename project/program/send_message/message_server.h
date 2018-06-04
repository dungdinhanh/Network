#ifndef _MESSAGE_SERVER_H_
#define _MESSAGE_SERVER_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libserver/server_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>
#include <libent/user.h>
#include <libio/database_api.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>
#include <libfdr/dllist.h>

typedef JRB Source;
typedef Dllist MessageQueue;
typedef Dllist OnlineList;


void setUpEnvironment();

void newOnline(int userID);

void deleteOnline(int userID);


OnlineList getNodeOnline(int userID);

int checkOnline(int userID);

MessageQueue getMessageQueue(int sender, int receiver);

void addMessageToSource(int sender, int receiver, char *message);

char *dequeueMessage(MessageQueue messageQueue);

char *readMessageFromSource(int sender, int receiver);

//server action

void sendAllUsers(int socketID, int sender);

#endif