#include "socket_api.c"


int main()
{
	char *buf = (char *)malloc(sizeof(char) * MAX_LINE);
	int listen_id = getListen();
	struct sockaddr_in cliaddr;
	socklen_t clilen;
	int n;
	while(1)
	{
		clilen = sizeof(cliaddr);
		int connfd = accept(listen_id, (struct sockaddr *) &cliaddr, &clilen);
		while ( (n = recv(connfd, buf, MAX_LINE,0)) > 0)  
		{
  			printf("%s","String received from and resent to the client:");
   			puts(buf);
   			sendMessage(connfd, buf);
   			// send(connfd, buf, n, 0);
  		}
			
 		if (n < 0) {
  			perror("Read error"); 
  			exit(1);
 		}
		close(connfd);
	}
	close(listen_id);
}