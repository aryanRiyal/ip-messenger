#include"header.h"

void serverExitClient(int socketfdDel) {
    int i = 0;
    int index = 0;
    
    // Graceful disconnect: Notify anyone who was chatting with this expiring client
    for (i = 0; i < server.totalClient; i++) {
        if (server.clientList[i].chatWithfd == socketfdDel) {
            char bufferSend[MB] = {0};
            memset(server.clientList[i].chatWith, 0, MAX_NAME_SIZE);
            server.clientList[i].chatWithfd = 0;
            snprintf(bufferSend, sizeof(bufferSend), "[System] : The user you were connected to has left. You are not connected to anyone. Hint: type LIST to view other active users.\n");
            serverSend(server.clientList[i].fileDes, bufferSend);
        }
    }

    // Remove the client from the active list
    for(i=0;i<server.totalClient;i++) { // Changed <= to < to avoid out-of-bounds
        if(server.clientList[i].fileDes == socketfdDel) {
            for(index = i; index< server.totalClient - 1; index++ ) { // Correct array shifting
                server.clientList[index] = server.clientList[index+1];
            }
            break;
        }
    }
    server.totalClient--;
    printf("Socket deleted  = [%d], totalclient = [%d]\n",socketfdDel,server.totalClient);
    close(socketfdDel);
}


