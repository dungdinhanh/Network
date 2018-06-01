#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <libauth/auth_client.h>
#include <libparse/parser.h>
#include <libclient/client_message.h>
#include <libent/user.h>
#include <libmessage/message_client.h>
#define SIZE_NAME_C 100

typedef struct Person{
    int id;
    char *name;
}Person;

typedef struct Group{
    int id;
    char *name;
}Group;


Person client;
Person partner;
Group group;

void setup();

void mainProg(int socketID);

void afterLogin(int socketID);

void chatToPerson(int socketID);

void *listenToServer(void *socketID);

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Ip address required");
        exit(1);
    }
    setup();
    int socketID = getConnect(argv[1]);
    //test login 
    // int login = logInClient(socketID);
    // close(socketID);
    // int registerResult = registerClient(socketID);
    mainProg(socketID);
    return 0;
}

void setup(){
    partner.id = -1;
    partner.name = (char *)malloc(sizeof(char) * SIZE_NAME_C);
    
    client.id = -1;
    client.name = (char *)malloc(sizeof(char) * SIZE_NAME_C);

    group.id = -1;
    group.name = (char *)malloc(sizeof(char) * SIZE_NAME_C);

    strcpy(partner.name, "");
    strcpy(client.name, "");
    strcpy(group.name, "");
}

void mainProg(int socketID)
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
            client.id = logInClient(socketID);
            if(client.id != -1)
            {
                afterLogin(socketID);
            }
        }

        if(choice == 2)
        {
           int registerResult = registerClient(socketID);
           if(registerResult == 1)
           {
               continue;
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
            chatToPerson(socketID);     
        }
        if(choice == 2)
        {

        }
    }while(choice != 3);
}


void chatToPerson(int socketID)
{
    // MessageClient messageClient = setListAllUsers(); 
    User *user = allUsersInSystemClient(socketID, client.id);
    int count = 0;
    int choice;
    while(1)
    {
        int count = 0;
        while(1)
        {
            if(user[count].id != -1)break;
            printf("%d. %s\n", user[count].id, user[count].userName);
            count++;
        }
        printf("your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice >= count || choice < 0)continue;
        else{
            partner.id = user[choice].id;
            strcpy(partner.name, user[choice].userName);
            break;
        }
    }
    pthread_t listenThread;
    int threadResult = pthread_create(&listenThread, NULL, listenToServer, (void *)socketID);
    if(threadResult)
    {
        printf("Error code in creating thread - Out task %d\n", threadResult);
        return;
    }

    while(1)
    {
        char *message = (char *)malloc(sizeof(char) * MAX_CLIENT_MESS);
        gets(message);
        sendMessage(socketID, message);
        //add signal in here
        if(strlen(message) == 1)
        {
            if(atoi(message) == -1)break;
        }
    }
}


void *listenToServer(void *socketID)
{
    int connectID = *(int *)socketID;
    while(1)
    {
        char *message = receiveMessage(socketID);
        if(message != NULL) printf("%s\n", message);
        else break;
    }
}