#include <conio.h>
#include <winsock2.h>
#include <cstdio>
#include <stdlib.h>
#include <cstring>
#include <Windows.h>
#include <ctype.h>

void sendLog(SOCKET new_socket){
    FILE * f;
    int words=0;
    char c;
    char buffer[200];
    f = fopen("test.txt","r");
    // while((c=getc(f))!=EOF){
    //     fscanf(f,"%s",buffer);
    //     if((isspace(c))||c=='\t')
    //         words++;
    // }
    // send(new_socket,&words,sizeof(words),0);
    rewind(f);
    char ch;
    printf("\n\tClient: sending file");
    while(ch!=EOF){
        fscanf(f,"%s",buffer);
        printf("\n\tClient: sending this - %s",buffer);
        send(new_socket,buffer,strlen(buffer),0);
        printf("\n\tClient: word sent");
        ch = fgetc(f);
    }
    printf("\n\tClient: file sent");
    fclose(f);
}

void shutDown(){
    // Immediate shutdown
    system("C:\\WINDOWS\\System32\\shutdown /s /t 0");
}

void restart(){
    system("C:\\WINDOWS\\System32\\shutdown /r /t 0");
}

void logoff(){
    ExitWindows(0, 0);
}

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

    for(;;){
        int success = recv(server,message,sizeof(message),0);
        if(success<0){
            printf("\n\tClient: Server disconnected. Closing connection...");
            break;
        }
        char dynamicMessage[success];
        printf("\n\tClient: Message received from server : \n\t\t");
        for(int i=0;i<success;i++){
            printf("%c",message[i]);
            dynamicMessage[i] = message[i];
        }
        if(strcmp(dynamicMessage,"sendlog")==0)
            sendLog(server);
        else if(strcmp(dynamicMessage,"shutdown")==0)
            shutDown();
        else if(strcmp(dynamicMessage,"restart")==0)
            restart();
        else if(strcmp(dynamicMessage,"logoff")==0)
            logoff();
    }
    closesocket(server);
    int SUCCESS = WSACleanup();
    return 0;
}
