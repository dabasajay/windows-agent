// Server side C/C++ program to demonstrate Socket programming
// ifconfig for ip's
#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <cstring>
using namespace std;

int main(){
	char addrr[30];
    int portNo;
    cout<<"\n\tServer: Enter address to listen on (Ex. 192.168.1.3, 127.0.0.1) : ";
    cin>>addrr;
    cout<<"\n\tServer: Enter Port Number (Ex. 8056, 8888): ";
    cin>>portNo;

    WSADATA WSAData;
    // WSAStartup() starts the WinSock API
    long SUCCESSFUL = WSAStartup(MAKEWORD(2,0), &WSAData);

	int server_fd, new_socket, valread;
	// Creating socket file descriptor
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		cout<<"\n\tServer: Socket failed";
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
		cout<<"\n\tServer: Bind failed";
		exit(EXIT_FAILURE);
	}

	// listen() tells a socket to listen for an incoming connection. It takes two arguments
	// 1. socket to listen on
	// 2. maximum no of connections
	if(listen(server_fd, SOMAXCONN) < 0){
		cout<<"\n\tServer: Listen failed";
		exit(EXIT_FAILURE);
	}
		
	cout<<"\n\tServer: Waiting for incoming connection";
	// accept() waits for a connection and wakes when a connection is
	// established, usually when coding the SERVER part of a client-server app.
	if(new_socket = accept(server_fd,(struct sockaddr *)&address,&addrlen)){
		cout<<"\n\tServer: Connection found";
		char message[50] = "You have connected to server!";
		// send() - method for sending data with TCP sockets
		send(new_socket,message,strlen(message),0);
		for(;;){
			cout<<"\n\tServer: Enter command to send to client\n\t\t";
			cin>>message;
			int success = send(new_socket,message,strlen(message),0);
			if(success<0){
				cout<<"\n\tServer: Client disconnected. Closing connection...";
				break;
			}
		}
	}
	else
		cout<<"\n\tServer: No connection found. Closing...";

	// closes an open socket
    closesocket(new_socket);
    // WSACleanup stops the Winsoch API
    int SUCCESS = WSACleanup();
    return 0;
}
