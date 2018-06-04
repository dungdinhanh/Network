#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <libauth/auth_client.h>
#include <libparse/parser.h>
#include <libclient/client_message.h>
#include <libent/user.h>
#include <libmessage/message_client.h>
#include <libgroup/group_client.h>
#define SIZE_NAME_C 100
#define SIZE_MAX_MESSAGE_CLIENT 2000

typedef struct Person{
    int id;
    char *name;
}Person;

// typedef struct Group{
//     int id;
//     char *name;
// }Group;


Person client;
Person partner;
Group group;

void setup();

void mainProg(int socketID);

void afterLogin(int socketID);

void chatToPerson(int socketID);

void chatToGroup(int socketID);

void *listenToServer(void *socketID);


void joinAGroup(int socketID, int sender);


int printGroupList(Group *group);

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

void setup()
{
    partner.id = -1;
    partner.name = (char *)malloc(sizeof(char) * SIZE_NAME_C);
    
    client.id = -1;
    client.name = (char *)malloc(sizeof(char) * SIZE_NAME_C);

    group = newGroup();


    strcpy(partner.name, "");
    strcpy(client.name, "");
    // strcpy(group.name, "");
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
            chatToGroup(socketID);
        }
    }while(choice != 3);
}


void chatToPerson(int socketID)
{
    // MessageClient messageClient = setListAllUsers(); 
    User *user = allUsersInSystemClient(socketID, client.id);
    if(user == NULL)
    {
        printf("No users \n");
        return;
    }
    // int count = 0;
    int choice;
    while(1)
    {
        int count = 0;
        while(1)
        {
            if(user[count].id == -1){
                // printf("no users : %s\n", user[count].userName);
                break;
            }
            printf("%d. %d - %s\n", count, user[count].id, user[count].userName);
            count++;
        }
        printf("your choice: ");
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice > count || choice < 0)continue;
        else{
            partner.id = user[choice].id;
            // printf("%d\n", partner.id);
            // printf("%s\n", user[choice].userName);
            strcpy(partner.name, user[choice].userName);
            requestSetTwoChatRoom(socketID, client.id, partner.id);
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
        char *message = (char *)malloc(sizeof(char) * SIZE_MAX_MESSAGE_CLIENT);
        gets(message);
        // printf("You: %s\n", message);
        sendMessageClient(socketID, message, client.id, partner.id);
        //add signal in here
        
        // if(strlen(message) == 1)
        // {
        //     if(atoi(message) == -1)
        //     {
        //         // pthread_cancel(&listenThread);
        //         partner.id = -1;
        //         break;
        //     }
        // }
    }
}

void chatToGroup(int socketID)
{
    int choice;
    do
    {
        printf("Menu\n");
        printf("1. Create group\n");
        printf("2. Join group \n");
        printf("3. Send message to group\n");
        printf("4. Exit\n");
        scanf("%d", &choice);
        while(getchar() != '\n');
        if(choice == 1)
        {
            printf("Input group name : ");
            char *groupName = (char *)malloc(sizeof(char) * MAX_CLIENT_MESS);
            gets(groupName);
            createGroupClient(socketID, client.id, groupName);   
        }

        if(choice == 2)
        {
            joinAGroup(socketID, client.id);            
        }

        if(choice == 3)
        {
            chatInGroup(socketID);
        }
        
    }while(choice != 4);

    
}


void *listenToServer(void *socketID)
{
    int connectID = (int)socketID;
    while(1)
    {
        char *message = receiveMessage(socketID);
       
        if(message != NULL)
        {
            MessageServer messageRC = serverJsonToStruct(message);
            printf("%s : %s\n", partner.name ,messageRC.message);
        }
        else break;
    }
}

void *listenToServerG(void *socketID)
{
    int connectID = (int)socketID;
    while(1)
    {
        char *message = receiveMessage(socketID);
       
        if(message != NULL)
        {
            MessageServer messageRC = serverJsonToStruct(message);
            printf("%s\n",messageRC.message);
        }
        else break;
    }
}

void joinAGroup(int socketID, int sender)
{
    Group *group = getListGroup(socketID, client.id);
    int choice;
    int count;
    do
    {
        count = printGroupList(group);
        scanf("%d", &choice);
        while(getchar() != '\n');
    }while(choice < 0 || choice >= count);

    joinGroup(socketID, client.id, group[choice].groupID);
}


int printGroupList(Group *group)
{
    int count = 0;
    while(1)
    {
        if(group[count].groupID == -1)break;
        printf("%d. %d - %s\n", count, group[count].groupID, group[count].groupName);
        count++;
    }
    return count;
}

void chatInGroup(int socketID)
{
    Group *groupList = getListGroupIn(socketID, client.id);
    int choice;
    int count;
    do
    {
        count = 0;
        while(1)
        {
            if(groupList[count].groupID == -1)break;
            printf("%d. %d - %s\n", count, groupList[count].groupID, groupList[count].groupName);
            count++;
        }
        if(count == 0)
        {
            printf("no group");
            break;
        }
        scanf("%d", &choice);
        while(getchar() != '\n');
    }while(choice < 0 || choice >= count);
    if(count = 0)return;
    group.groupID = groupList[choice].groupID;
    strcpy(group.groupName, groupList[choice].groupName);
    requestGroupChatRoom(client.id, group.groupID, socketID);

    pthread_t listenThread;
    int threadResult = pthread_create(&listenThread, NULL, listenToServerG, (void *)socketID);
    if(threadResult)
    {
        printf("Error code in creating thread - Out task %d\n", threadResult);
        return;
    }

    while(1)
    {
        char *message = (char *)malloc(sizeof(char) * SIZE_MAX_MESSAGE_CLIENT);
        gets(message);
        // printf("You: %s\n", message);
        //sendMessageClient(socketID, message, client.id, partner.id);
        sendMessageGroupClient(client.id, group.groupID, client.name ,message, socketID);
        //add signal in here
        
        // if(strlen(message) == 1)
        // {
        //     if(atoi(message) == -1)
        //     {
        //         // pthread_cancel(&listenThread);
        //         partner.id = -1;
        //         break;
        //     }
        // }
        free(message);
    }
    //add more
}