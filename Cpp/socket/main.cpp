#include <iostream>
#include <winsock2.h>
#include <Windows.h>
#include <cstring>
using namespace std;
int main(){
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_addr.s_addr = inet_addr("192.168.1.3");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8056);
    cout<<"Starting...\n";
    if(connect(server, (SOCKADDR *)&addr, sizeof(addr))<0){
        cout<<"\nConnection failed";
        return -1;
    }
    cout<<"\nConnected to server!";

    char buffer[20]={'S'};
    send(server, buffer, sizeof(buffer), 0);
    cout<<"\nFile requested"<< endl;

    char *message;
    int valread = recv(server,message,20,0);

    cout<<"\nFile received";
    STARTUPINFO startInfo = {0};
    PROCESS_INFORMATION processInfo = {0};
    BOOL b5success = CreateProcess(TEXT("//DABASAJAY/test/s1.exe"),NULL,NULL,NULL,FALSE,FALSE,NULL,NULL,&startInfo,&processInfo);
    if(b5success){
        cout<<"\nProcess Started";
    }
    else{
        cout<<"\nError to start the process : ";
    }
    closesocket(server);
    WSACleanup();
    return 0;
}
