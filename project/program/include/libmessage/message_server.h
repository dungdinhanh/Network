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



void sendAllUsers(int socketID, int sender);

#endif