#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libauth/auth_client.h>



int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Ip address required");
        exit(1);
    }
    int socketID = getConnect(argv[1]);
    //test login 
    // int login = logInClient(socketID);
    // close(socketID);
    int registerResult = registerClient(socketID);
    return 0;
}