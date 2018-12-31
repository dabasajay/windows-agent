#include <cstdio>
#include <conio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <Windows.h>
#include <cstring>

void sendLog(SOCKET new_socket){
    FILE * fp;
    fp = fopen("test.txt","rb");
    if(fp==NULL){
        printf("\n\tClient: File open error");
        return;   
    }
    printf("\n\tClient: Sending Logs");
    while(1){
        /* First read file in chunks of 256 bytes */
        char buff[1024]={0};
        int nread = fread(buff,1,1024,fp);       
        /* If read was success, send data. */
        if(nread>0){
            // printf("\n\tClient: Sending : %s",buff);
            // write(new_socket, buff, nread);
            send(new_socket,buff,sizeof(buff),0);
        }
        if(feof(fp) || ferror(fp))
            break;
    }
    fclose(fp);
    printf("\n\tClient: Logs Sent");
}

void shutdown(){
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
        // cut off potential tailing \n
        dynamicMessage[strcspn(dynamicMessage, "\n")] = '\0';
        if(strcmp(dynamicMessage,"sendlog")==0){
            sendLog(server);
        }
        else if(strcmp(dynamicMessage,"shutdownuser")==0){
            printf("\n\tClient: Shutting down...");
            shutdown();
        }
        else if(strcmp(dynamicMessage,"logoffuser")==0){
            printf("\n\tClient: Logging off...");
            logoff();
        }
        else if(strcmp(dynamicMessage,"restartuser")==0){
            printf("\n\tClient: Restarting...");
            restart();
        }
    }
    closesocket(server);
    int SUCCESS = WSACleanup();
    return 0;
}