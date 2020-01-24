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
#define PORT	7777
#define BUF_SIZE	1024

void* recv_thread(void *d)
{

    char buf[BUF_SIZE];
    char buff[BUF_SIZE];
    int tfd = *(int *)d;
    int recvbytes;
    if(tfd>0)
    {
        while(1)
        {    bzero(buf, sizeof(buf));	// 清空缓冲
        if ((recvbytes = recv(tfd, buf, BUF_SIZE, 0)) == -1)   	// 等待接收数据
        {
            perror("recv");
            break;
        }
        else
        {
            if(strlen(buf)>=12)

              {
                 if(buf[0]=='#'&& buf[1]=='#')
                 printf("receive from %d(socket): %s\n", tfd, buf);	// 打印接收数据
                 {
                  strcpy(buff,buf);

                        int i = 0;
            for(i=0;i<strlen(buf);i++)
            {
                buf[i]=buf[i+2];
            }
                        int j = 0;

           for(i = 0; i < 10; i++)

            {

           for(j = 0; j < 10-i-1; j++)

                {

                if(buf[j]>buf[j + 1])

                        {

                            int temp = buf[j];

                            buf[j] = buf[j + 1];

                            buf[j + 1] = temp;

                        }

                }

            }


                   }

                 }
        strcat(buff,"-");
        strcat(buff,buf);
        strcat(buff,":17041129 YYC");
        strcpy(buf,buff);
         send(tfd,buf,strlen(buf),0);
          }
           usleep(1000);
        }


    }

 return 0;
}


int main(int argc, char *argv[])
{
    int sockfd, sendbytes,recvbytes;
    char buf[BUF_SIZE];
    struct hostent *host;
    struct sockaddr_in serv_addr;

    if (argc < 2)   	// 检查程序参数个数
    {
        printf("USAGE: ./tclient Hostname(or ip address)\n");
        exit(1);
    }

    // 检查程序参数指定的服务器地址
    if ((host = gethostbyname(argv[1])) == NULL)
    {
        perror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // 创建一个流式socket
    {
        perror("socket");
        exit(1);
    }

    // 初始化serv_addr结构体变量
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
    bzero(&(serv_addr.sin_zero), 8);

    // 连接服务器
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    pthread_t id;
    pthread_create(&id,NULL,recv_thread,&sockfd);
    // 显示连接信息
    printf("connect to server %s...\nInput the msg to send:\n", argv[1]);
    while (1)     	// 循环发送、接收服务器信息
    {
        bzero(buf, sizeof(buf));	// 清空缓冲
        if (fgets(buf, BUF_SIZE, stdin))    	// 终端输入一行数据
        {
            if (strcmp(buf, "exit\n") == 0)    break;	// 判断是否退出循环
            if ((sendbytes = send(sockfd, buf, strlen(buf), 0)) == -1)    	// 是否发送成功
            {
                perror("send");
                exit(1);
            }
        }
       bzero(buf, sizeof(buf));	// 清空缓冲
        if ((recvbytes = recv(sockfd, buf, BUF_SIZE, 0)) == -1)   	// 等待接收数据
        {
           perror("recv");
           exit(1);
       }
        else    printf("receive from %d(socket): %s\n", sockfd, buf);	// 打印接收数据
    }

    close(sockfd);	// 关闭socket
    return 0;
}

