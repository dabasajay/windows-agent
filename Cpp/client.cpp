// Link libws_v2 library with this using linker in codeblock project->build options. path : codeblocks/mingw/lib/
#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
using namespace std;
int main(){
    char addrr[30];
    int portNo;
    cout<<"\nEnter address to connect to (Ex. 192.168.1.3, 127.0.0.1) : ";
    cin>>addrr;
    cout<<"\nEnter Port Number (Ex. 8056, 8888): ";
    cin>>portNo;
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr(addrr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNo);
    cout<<"\nConnecting to server...";
    if(connect(server, (SOCKADDR *)&addr, sizeof(addr))<0){
        cout<<"\nConnection failed \nPress Enter to exit the program";
        getch();
        return -1;
    }
    cout<<"\nConnected to server!";

    // char buffer[20]={'S'};
    // send(server, buffer, sizeof(buffer), 0);

    char *message;
    for(;;){
        int valread = recv(server,message,1024,0);
        cout<<"\nCommand Received : "<<message;
        if ((strcmp(message, "exit")) == 0) { 
            cout<<"\nClient Exit..."; 
            break; 
        } 
    }
    closesocket(server);
    WSACleanup();
    return 0;
}
