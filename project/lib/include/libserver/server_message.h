#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libconfig/message.h>
#define SUCCESS 0
#define FAILS 1
#define SEND_MESSAGE 2
#define LIST_OBJECT 3



MessageServer setSuccessfulResponse(int code, int senderId);

MessageServer setFailResponse(int code);

MessageServer setSendMessageToClient(char *message, char*senderName, int sender_id, int receiver_id, int group_id);

MessageServer setList();