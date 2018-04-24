

#define MAX_LINE 4096 //max text line
#define SERVER_PORT 3000 // server port
#define LISTENQ 100 // maximum number of client connection
//for server
struct sockaddr_in serverConfigure();
int initListen(struct sockaddr_in server_address);
int getListen();



//for client
//struct sockaddr_in clientConfigure();
// int connectResquest(char *server_ip); // -1 if it can not connect , return socket_id as id for this connection

struct sockaddr_in clientServerConfigure(char *server_ip);

int connectAction(int socket_id, struct sockaddr_in server);

int getConnect(char *server_ip); // return socket_id for the connection -1 if it can not connect , return socket_id as id for this connection

//for both
void sendMessage(int socket_id, char *message);


char * receiveMessage(int socket_id);