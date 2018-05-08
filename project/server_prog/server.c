#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libauth/auth_server.h>
#include <libio/database_api.h>

int main()
{
    int listenID = getListen();
    int connectID = getAccept(listenID);
    startConnection();
    // logInServer(connectID);
    registerServer(connectID);
    //close(connectID);
    //close(listenID);
    // close(connectID);
    // close(listenID);
    closeConnection();
    return 0;
}