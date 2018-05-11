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



void mainProg(int socketID);
{
    int choice;
    do
    {
        printf("Menu\n");
        printf("1. Sign in\n");
        printf("2. Sign up\n");
        printf("3. Exit\n");
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice == 1)
        {
            int login = logInClient(socketID);
            if(login == 1)
            {
                
            }
        }

        if(choice == 2)
        {
           int registerResult = registerClient(socketID);
           if(registerResult == 1)
           {
               
           }
        }
    }
    while(choice != 3);
}


void afterLogin(int socketID)
{
    int choice;
    do
    {
        printf("Menu\n");
        printf("1. Chat to a person\n");
        printf("2. Chat to a group \n");
        printf("3. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        if(choice == 1)
        {

        }

        if(choice == 2)
        {

        }
    }while(choice != 3);
}


void chatToPerson(int socketID)
{
    
}