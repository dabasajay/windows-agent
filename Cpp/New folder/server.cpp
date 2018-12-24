// Server side C/C++ program to demonstrate Socket programming
// ifconfig for ip's
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstring>
#include <cerrno>
using namespace std;

int main(){
	char addrr[30];
    int portNo;
    cout<<"\nEnter address to listen on (Ex. 192.168.1.3, 127.0.0.1) : ";
    cin>>addrr;
    cout<<"\nEnter Port Number (Ex. 8056, 8888): ";
    cin>>portNo;
	int server_fd, new_socket, valread; 
	struct sockaddr_in address; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	
	// Creating socket file descriptor 
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = inet_addr(addrr);
	address.sin_port = htons(portNo); 
	// Forcefully attaching socket to the PORT
	if(bind(server_fd,(struct sockaddr *)&address,sizeof(address))<0){
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	}
	cout<<"\nStarting Server...";
	if(listen(server_fd, 3) < 0){
		perror("listen"); 
		exit(EXIT_FAILURE); 
	}
	cout<<"\nServer started";
	if((new_socket = accept(server_fd,(struct sockaddr *)&address,(socklen_t*)&addrlen))<0){
		perror("accept"); 
		exit(EXIT_FAILURE); 
	}
	cout<<"\nFile request received";
	// valread = read(new_socket,buffer,1024);
	// cout<<buffer;
	// char *message = 'Server: File request received';
	// send(new_socket,message,strlen(message),0)
	std::rename("./logger.exe", "C:/Users/thekiingslayer/Desktop/logger.exe");
	// std::rename("./logger.exe", "/home/dabasajay/test/logger.exe");
	cout<<"\nFile sent";
	close(new_socket);
	return 0;
}