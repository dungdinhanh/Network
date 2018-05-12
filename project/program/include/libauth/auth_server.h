#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libserver/server_message.h>
#include <libsocket/socket_api.h>
#include <libparse/parser.h>
#include <libio/database_api.h>

#define MAX_LOGIN 1000


int logInServer(int connID, char *userName, char *password);

int registerServer(int connID, char *userName, char *password);