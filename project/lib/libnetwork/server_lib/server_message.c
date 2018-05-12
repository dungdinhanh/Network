#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libconfig/message.h>
#include "server_message.h"

MessageServer setSuccessfulResponse(int code, int senderID)
{
	MessageServer messageServer = newMessageServer();
	messageServer.code = code;
	messageServer.method = SUCCESS;
	messageServer.sender = senderID;
	return messageServer;
}

MessageServer setFailResponse(int code)
{
	MessageServer messageServer = newMessageServer();
	messageServer.code = code;
	messageServer.method = FAILS;
	return messageServer;
}

MessageServer setSendMessageToClient(char *message, char*senderName, int sender_id, int receiver_id, int group_id)
{
	MessageServer messageServer = newMessageServer();
	messageServer.method = SEND_MESSAGE;
	messageServer.sender = sender_id;
	messageServer.receiver = receiver_id;
	setMessageServer(messageServer, message);
	setSenderNameServer(messageServer, senderName);
	return messageServer;
}

MessageServer setList()
{
	MessageServer messageServer = newMessageServer();
	messageServer.method = LIST_OBJECT;
	return messageServer;
}


