#ifndef _GROUP_CLIENT_H_
#define _GROUP_CLIENT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libent/group.h>
#include <libent/user.h>
#include <libclient/client_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>
#include "group_client.h"

void createGroupClient(int socketID, int sender, char *groupName);

void joinGroup(int socketID, int sender, int groupID);

Group * getListGroup(int socketID, int sender);

Group * getListGroupIn(int socketID, int sender);


void requestGroupChatRoom(int sender, int groupID, int socketID);

void sendMessageGroupClient(int sender, int groupID, char *userName ,char *message ,int socketID);
#endif