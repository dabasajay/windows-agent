#include <iostream>
#include <winsock2.h>
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

    char buffer[1024]={'A', 'J', 'A', 'Y'};
    send(server, buffer, sizeof(buffer), 0);
    cout<<"\nMessage sent!"<< endl;

    char *message;
    int valread = recv(server,message,1024,0);
    cout<<"\n"<<message;

    closesocket(server);
    WSACleanup();
    cin.get();
    return 0;
}
