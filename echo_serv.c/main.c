#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>h>
#include<errno.h>
#define ECHO_PORT 8080
#define MAX_CLIENT_NUM 10
int main()
{
    int sock_fd;
    struct sockaddr_in serv_addr;
    int clientfd;
    struct sockaddr_in clientAdd;
    char buff[101];
    socklen_t len;
    int n;
    sock_fd=socket(AF_INET,SOCK_STREAM,0);
    if(socket==-1){
        perror("create socket error");
        return 0;
    }
    else {
        printf("Sucess to create socket %d\n",sock_fd);

    }
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ECHO_PORT);
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    bzero(&(serv_addr.sin_zero), 8);
    if(bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))!=0){
        printf("bind address fail!%d\n",errno);
        close(sock_fd);
        return 0;

    }
    else {
    printf("Sucess to binf address!\n");

    }
    if(listen(sock_fd,MAX_CLIENT_NUM)!=0){
        perror("listen socket error\n");
        close(sock_fd);
        return 0;
    }
    else {

    printf("Sucess to listen\n");
    }
    len=sizeof(clientAdd);
    clientfd=accept(sock_fd,(struct sockaddr*)&clientAdd,&len);
    if(clientfd<=0){
        perror("accept() error!\n");
        close(sock_fd);
        return 0;
    }
    while((n=recv(clientfd,buff,100,0))>0){

        printf("number of receive bytes = %d data = %s\n",n,buff);

        send(clientfd,buff,n,0);
        if(strncmp(buff,"quit",4)==0);
        break;
    }
    close(clientfd);
    close(sock_fd);
    return 0;
}
