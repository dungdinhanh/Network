#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socket_api.h"

//for server
struct sockaddr_in serverConfigure(){
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = SERVER_PORT;
	return server_address;
}

int initListen(struct sockaddr_in server_address)
{
	int listen_id = socket(AF_INET, SOCK_STREAM, 0);
	bind(listen_id, (struct sockaddr *)&server_address, sizeof(server_address));
	listen(listen_id, LISTENQ);
	return listen_id;
}

int getListen() // get listen_id for the connection
{
	//int listen_id = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_address = serverConfigure();
	return initListen(server_address);
}



//for client
struct sockaddr_in clientServerConfigure(char *server_ip){
	struct sockaddr_in server; 
	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(server_ip);
	server.sin_port = SERVER_PORT;
	return server;
}

int connectAction(int socket_id, struct sockaddr_in server)
{
	return connect(socket_id, (struct sockaddr*) &server, sizeof(server));
}

int getConnect(char *server_ip) // return socket_id for the connection
{
	struct sockaddr_in server = clientServerConfigure(server_ip);
	int socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_id < 0)
	{
		perror("Problem in creating socket");
		exit(2);
		return -1;
	}
	int connect_res = connectAction(socket_id, server);
	if( connect_res < 0)
	{
		perror("Error in connecting to server");
		exit(3);
		return -1;
	}
	return socket_id;
}



//for both
void sendMessage(int socket_id, char *message) // take socket_id as client and accept_id as server
{
	send(socket_id, message, strlen(message), 0);
}


char * receiveMessage(int socket_id)
{
	char *message = (char *)malloc(sizeof(char) * 100);
	if(recv(socket_id, message, MAX_LINE, 0) == 0)
	{
		perror("The server terminated prematurely");
		exit(4);
		return NULL;
	}
	return message;
}

