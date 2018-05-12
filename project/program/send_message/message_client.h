#define MAX_USERS_IN 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libserver/server_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>
#include <libent/user.h>
#include "message_client.h"


void sendMessageClient(int socketID, char *message, int sender, int receiver);

User *allUsersInSystemClient(int socketID, int sender);
