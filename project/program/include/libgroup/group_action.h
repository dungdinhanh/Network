#ifndef _GROUP_ACTION_H_
#define _GROUP_ACTION_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libent/group.h>
#include <libent/user.h>
#include <libparse/parser.h>
#include <libserver/server_message.h>
#include <libio/database_api.h>
#include <libsocket/socket_api.h>
#include <libfdr/dllist.h>
#include <libfdr/jrb.h>
#include <libfdr/jval.h>


typedef JRB GroupSource;
typedef Dllist GroupList;

// extern GroupSource gSource;
// extern GroupList gList;

void setUpGroupSource();

Dllist getMessageGroupQueue(int groupID, int receiver);

void addMessageToGroupSource(int groupID, int receiver,char *senderName ,char *message);

char *getMessageFromQueue(Dllist messageQueue);

char *readMessageFromGroupSource(int groupID, int receiver);


void sendSussesfulResponse(int connectionID);


void sendFailResponse(int connectionID);


void createGroup(char *groupName, int creator, int connectionID);

void insertUserToGroup(int sender, int group, int connectionID);

void sendListGroups(int sender, int connectionID);

void sendListGroupsIn(int sender, int connectionID);

#endif