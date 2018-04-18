#include "socket_api.c"


int main(int argc, char **args)
{
	int sockfd = getConnect(args[1]);
	char *sendline = (char *)malloc(sizeof(char) * MAX_LINE);
	char *recvline = (char *)malloc(sizeof(char) * MAX_LINE);
	while (fgets(sendline, MAX_LINE, stdin) != NULL) {
		recvline = (char *)malloc(sizeof(char) * 1000);
  		sendMessage(sockfd, sendline);
		
		recvline = receiveMessage(sockfd);
  		// if (recv(sockfd, recvline, MAX_LINE,0) == 0){
   	// 	//error: server terminated prematurely
   	// 	perror("The server terminated prematurely"); 
   	// 	exit(4);}

  	printf("%s", "String received from the server: ");
  	fputs(recvline, stdout);
	}
 exit(0);
}