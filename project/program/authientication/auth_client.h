#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libsocket/socket_api.h>
#include <libparse/parser.h>

#define MAX_LOGIN 1000

int logInClient(int socketID);


int registerClient(int socketID);
