// Link libws_v2 library with this using linker in codeblock project->build options. path : codeblocks/mingw/lib/
#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <cstring>
using namespace std;
int main(){
    char addrr[30];
    int portNo;
    cout<<"\n\tClient: Enter address to connect to (Ex. 192.168.1.3, 127.0.0.1) : ";
    cin>>addrr;
    cout<<"\n\tClient: Enter Port Number (Ex. 8056, 8888): ";
    cin>>portNo;
    
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr(addrr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNo);

    WSADATA WSAData;
    // WSAStartup() starts the WinSock API
    long SUCCESSFUL = WSAStartup(MAKEWORD(2,0), &WSAData);

    // process for initiating a TCP socket connection
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    
    cout<<"\n\tClient: Connecting to server...";
    // connect() connects a client to a server that is in the "listening" state
        // and set to "accept" a connection
    if(connect(server, (SOCKADDR *)&addr, sizeof(addr))<0){
        cout<<"\n\tClient: Connection failed \n\tClient: Press Enter to exit the program";
        getch();
        return -1;
    }
    cout<<"\n\tClient: Connected to server!";

    char message[200];
    for(;;){
        int success = recv(server,message,sizeof(message),0);
        if(success<0){
            cout<<"\n\tClient: Server disconnected. Closing connection...";
            break;
        }
        cout<<"\n\tClient: Message received from server : \n\t\t";
        for(int i=0;i<success;i++)
            cout<<message[i];
    }

    // closes an open socket
    closesocket(server);
    // WSACleanup stops the Winsoch API
    int SUCCESS = WSACleanup();
    return 0;
}