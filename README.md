Chat Application using TCP SOCKET
Basic TCP client-server-client communication using select() system call :

(for Linux)
Build Steps:

go the server directory and then run make command for compiling the server code.
Similarly, go the client directory and then run make command for compiling the client code.
Execute Steps:

Use ./runS to run the server in server directory.
Use ./runC client_name serverIPAddress in client directory on other terminals (EX. ./runC omkar 127.0.0.1)
Functionalities for client :
Use the following Command after running the client.

1.LIST : It gives list of all connected clients.

2.CONNECT : It is used to connect with another client which is present in list. (NOTE: If you want to send the message to the another client then step first is use CONNECT followed with message receiver client name).

3.ALL: It is used to send the broadcast message to all connected client to the server. (NOTE: There is no need to run CONNECT command simply run ALL with the message you want to send for all other clients which is present in list).

4.EXIT: It used to exit or disconnect with the server . It will terminate the client.

NOTE:
After terminating the server as well as client, use make clean command for cleaning all the .o extension files and output file from both the directories server and client .
