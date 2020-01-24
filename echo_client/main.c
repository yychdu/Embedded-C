#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>

#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define ECHO_PORT 8080
#define MAX_COMMAND 5
int main()
{
    int sock_fd;
    struct sockaddr_in serv_addr;
    char *buff[MAX_COMMAND]={"abc","def","test","hello","quit"};
    char tmp_buf[100];
    int n,i;
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
    if(-1==connect(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)))

    {
        perror("connect() error\n");
        close(sock_fd);
        return 0;

    }
    printf("Sucess connect to server!\n");

    for(i=0;i<MAX_COMMAND;i++){
        send(sock_fd,buff[i],100,0);
        n=recv(sock_fd,tmp_buf,100,0);
        tmp_buf[n]='\0';
        printf("data send:%s receive:%s\n",buff[i],tmp_buf);
       if(strncmp(buff,"quit",4)==0);
        break;
    }
    close(sock_fd);
    return 0;
}
