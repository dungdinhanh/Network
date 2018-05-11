#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libconfig/message.h>
#include <libclient/client_message.h>
#include <libserver/server_message.h>
#include <libparse/parser.h>
#include <libsocket/socket_api.h>


void sendMessageClient(int socketID, char *message, int sender, int receiver)
{
    MessageClient messageClient = setSendMessage(message, sender, receiver);
    char *messageJSON = clientStructToJson(messageClient);
    sendMessage(socketID, messageJSON);
    //return 1;
}


