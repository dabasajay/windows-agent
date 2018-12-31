#include <cstdio>
#include <conio.h>
#include <winsock2.h>
#include <stdlib.h>

void receiveLogs(int new_socket){
	FILE *fp;
	char recvBuff[1024];
	fp = fopen("test_received.txt","ab");
	if(fp==NULL){
		printf("\n\tServer: Error opening file");
		return;
    }
    printf("\n\tServer: Receiving Logs");
    int success = recv(new_socket,recvBuff,sizeof(recvBuff),0);
	char dynamicMessage[success];
	for(int i=0;i<success;i++)
		dynamicMessage[i] = recvBuff[i];
	// printf("\n\tServer: Received : %s",dynamicMessage);
	fprintf(fp, "%s ",dynamicMessage);
    fclose(fp);
    printf("\n\tServer: Logs Received");
}

int main(){
	char addrr[15];
    int portNo;
    printf("\n\tServer: Enter address to listen on (Ex. 192.168.1.3, 127.0.0.1) : ");
    scanf("%s",addrr);
    printf("\n\tServer: Enter Port Number (Ex. 8056, 8888): ");
    scanf("%d",&portNo);

    WSADATA WSAData;
    // WSAStartup() starts the WinSock API
    long SUCCESSFUL = WSAStartup(MAKEWORD(2,0), &WSAData);

	int server_fd, new_socket, valread;
	// Creating socket file descriptor
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		printf("\n\tServer: Socket failed");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in address;
	int addrlen = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(addrr);
	address.sin_port = htons(portNo);
	// bind() binds a socket to the SOCKADDR_IN structure containing the
	// IP and port used to build the connection
	if(bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
		printf("\n\tServer: Bind failed");
		exit(EXIT_FAILURE);
	}

	// listen() tells a socket to listen for an incoming connection. It takes two arguments
	// 1. socket to listen on
	// 2. maximum no of connections
	if(listen(server_fd, SOMAXCONN) < 0){
		printf("\n\tServer: Listen failed");
		exit(EXIT_FAILURE);
	}

	printf("\n\tServer: Waiting for incoming connection");
	// accept() waits for a connection and wakes when a connection is
	// established, usually when coding the SERVER part of a client-server app.
	if(new_socket = accept(server_fd,(struct sockaddr *)&address,&addrlen)){
		printf("\n\tServer: Connection found");
		char message[50] = "You have connected to server!";
		// send() - method for sending data with TCP sockets
		send(new_socket,message,strlen(message),0);
		for(;;){
			printf("\n\tServer: Enter command to send to client\n\t\t");
			scanf("%s",message);
			int success = send(new_socket,message,strlen(message),0);
			if(success<0){
				printf("\n\tServer: Client disconnected. Closing connection...");
				break;
			}
			if(strcmp(message,"sendlog")==0)
				receiveLogs(new_socket);
		}
	}
	else
		printf("\n\tServer: No connection found. Closing...");

	// closes an open socket
    closesocket(new_socket);
    // WSACleanup stops the Winsoch API
    int SUCCESS = WSACleanup();
    return 0;
}