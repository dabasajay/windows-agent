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

    char buffer[20]={'S'};
    send(server, buffer, sizeof(buffer), 0);
    cout<<"\nFile requested"<< endl;

    char *message;
    int valread = recv(server,message,20,0);

    cout<<"\nFile received";
    STARTUPINFO startInfo = {0};
    PROCESS_INFORMATION processInfo = {0};
    BOOL b5success = CreateProcess(TEXT("C:/Users/thekiingslayer/Desktop/logger.exe"),NULL,NULL,NULL,FALSE,FALSE,NULL,NULL,&startInfo,&processInfo);
    // BOOL b5success = CreateProcess(TEXT("//DABASAJAY/test/logger.exe"),NULL,NULL,NULL,FALSE,FALSE,NULL,NULL,&startInfo,&processInfo);
    if(b5success){
        cout<<"\nProcess Started\n\n";
    }
    else{
        cout<<"\nError to start the process \nPress Enter to exit the program";
        getch();
    }
    closesocket(server);
    WSACleanup();
    return 0;
}
