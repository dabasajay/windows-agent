#include <conio.h>
#include <winsock2.h>
#include <cstdio>
#include <stdlib.h>
#include <ctype.h>
int main(){
    char addrr[15];
    int portNo;
    printf("\n\tClient: Enter address to connect to (Ex. 192.168.1.3, 127.0.0.1) : ");
    scanf("%s",addrr);
    printf("\n\tClient: Enter Port Number (Ex. 8056, 8888): ");
    scanf("%d",&portNo);
    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr(addrr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(portNo);
    WSADATA WSAData;
    long SUCCESSFUL = WSAStartup(MAKEWORD(2,0), &WSAData);
    SOCKET server = socket(AF_INET, SOCK_STREAM, 0);
    printf("\n\tClient: Connecting to server...");
    if(connect(server, (SOCKADDR *)&addr, sizeof(addr))<0){
        printf("\n\tClient: Connection failed \n\tClient: Press Enter to exit the program");
        getch();
        return -1;
    }
    printf("\n\tClient: Connected to server!");
    char message[30];

    FILE * f;
    int words=0;
    char c;
    char buffer[200];
    f = fopen("text.txt","r");
    while(c!=EOF){
        fscanf(f,"%s",buffer);
        // send
        c = fgetc(f);
    }
    // rewind (f);
    for(;;){
        int success = recv(server,message,sizeof(message),0);
        if(success<0){
            printf("\n\tClient: Server disconnected. Closing connection...");
            break;
        }
        printf("\n\tClient: Message received from server : \n\t\t");
        for(int i=0;i<success;i++)
            printf("%c",message[i]);
    }
    closesocket(server);
    int SUCCESS = WSACleanup();
    return 0;
}
