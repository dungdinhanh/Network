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
#include "message_server.h"



void sendAllUsers(int socketID, int sender)
{
    MessageServer messageServer = setList();
    User *user = getAllUser();
    int count = 0;
    while(1)
    {
        if(user[count].id == -1)break;
        Object object = initObject();
        strcpy(object.user, user[count].userName);
        object.id = user[count].id;
        addObject(messageServer, object);
    }
    char *message = serverStructToJson(messageServer);
    sendMessage(socketID, message);
}

