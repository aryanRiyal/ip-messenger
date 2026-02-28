#include "header.h"
//processing the received data from clients

//find index of the client data structure from client socket
int findClientIndexList( int socket) {
    int index = 0;
    for(int i = 0; i<server.totalClient; i++) {
        if(server.clientList[i].fileDes == socket) {
            index =i;
        }
    }
    return index;
}

//find index of the client data structure from client name
int findClientIndexName( char *name) {
    int index = 0;
    for(int i = 0; i<server.totalClient; i++) {
        if(strcmp(server.clientList[i].cname,name) == 0) {
            index =i;
        }
    }
    return index;
}

int processRecvData( int socket, char *buffer) {
    char connectedClient[MAX_NAME_SIZE];
    char bufferSend[MB] = {0};
    char toAll[800];
    int indexSender = 0;
    int indexReceiver = 0;
    int len = 0;
    indexSender = findClientIndexList(socket);

    //MENU
    if(strncmp( buffer, "LIST", 4) ==0) {
        memset( buffer, 0, MB);
        for(int i=0;i<server.totalClient;i++) {
            strcat( buffer, server.clientList[i].cname);
            strcat( buffer,";");
        }
        serverSend( socket, buffer);
        memset( buffer, 0, MB);
        return 0;
    }
    if(strncmp(buffer, "CONNECT",7) == 0) {
        // Graceful disconnect: Notify the previous user if we were already connected to someone
        if (strlen(server.clientList[indexSender].chatWith) != 0) {
            snprintf(bufferSend, sizeof(bufferSend), "[System] : %s has disconnected from you.\n", server.clientList[indexSender].cname);
            if (server.clientList[indexSender].chatWithfd > 0) {
                serverSend(server.clientList[indexSender].chatWithfd, bufferSend);
            }
        }

        sscanf(buffer,"CONNECT%*[ ]%s",connectedClient);
        strcpy(server.clientList[indexSender].chatWith, connectedClient);

        indexReceiver = findClientIndexName( server.clientList[indexSender].chatWith);
        server.clientList[indexSender].chatWithfd = server.clientList[indexReceiver].fileDes;
        serverSend( server.clientList[indexSender].fileDes, CONNECTED);

        // Notify the new person that we connected
        snprintf(bufferSend, sizeof(bufferSend), "[System] : %s has connected with you. (Hint: You must also type 'CONNECT %s' to reply back.)\n", server.clientList[indexSender].cname, server.clientList[indexSender].cname);
        serverSend(server.clientList[indexSender].chatWithfd, bufferSend);

        return 0;
    }

    if(strncmp(buffer, "DISCONNECT", 10) == 0) {
        if (strlen(server.clientList[indexSender].chatWith) != 0) {
            snprintf(bufferSend, sizeof(bufferSend), "[System] : %s has disconnected from you.\n", server.clientList[indexSender].cname);
            if (server.clientList[indexSender].chatWithfd > 0) {
                serverSend(server.clientList[indexSender].chatWithfd, bufferSend);
            }
            // Clear out the tracking fields properly
            memset(server.clientList[indexSender].chatWith, 0, MAX_NAME_SIZE);
            server.clientList[indexSender].chatWithfd = 0;
            serverSend(server.clientList[indexSender].fileDes, "Disconnected from current chat.\n");
        } else {
            serverSend(server.clientList[indexSender].fileDes, "You are not currently connected to anyone.\n");
        }
        return 0;
    }

       if(strncmp(buffer,"EXIT",4) == 0){
       // printf("\nsocket=%d\nconnected with=%d\n\n", socket, server.clientList[indexSender].chatWithfd);
       // printf("%d\n",server.totalClient);
       serverExitClient(socket);
       // printf("%d\n",server.totalClient);
       return 0;
       }

    if(strncmp(buffer,"ALL",3)==0){
        sscanf(buffer,"ALL%*[ ]%[^\n]",toAll);
        char broadcast[20]="BROADCAST BY";
        for(int i=0;i<server.totalClient;i++){
            if(i==indexSender){
                continue;
            }
            snprintf( bufferSend, sizeof(bufferSend), "[%s %s] : %s\n", broadcast, server.clientList[indexSender].cname, toAll);
            serverSend( server.clientList[i].fileDes, bufferSend);
        }
        return 0;
    }

    if(strlen( server.clientList[indexSender].chatWith) != 0){
        snprintf( bufferSend, sizeof(bufferSend),"[%s] : %s", server.clientList[indexSender].cname, buffer);
        printf( "Buffer  = %s",bufferSend);
        serverSend( server.clientList[indexSender].chatWithfd, bufferSend);
    }
    return 0;
}
