
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
    char str1[BUF_SIZE]="##";
    char str3[BUF_SIZE]=":17041129 杨宇晨";
    char str2[BUF_SIZE];
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



                 if(buf[0]=='#'&& buf[1]=='#')
                 printf("receive from %d(socket): %s\n", tfd, buf);	// 打印接收数据
                int i,t;             //t记录临时加的数
                int sum =0;
                for(i=2; buf[i]; i++)
                {
                    if(buf[i]>='0'&&buf[i]<='9')
                        t=buf[i]-'0';       //当字符是0~9时保持原数不变
                    if(buf[i]>='a'&&buf[i]<='z')
                        t=buf[i]-'a'+10;
                    if(buf[i]>='A'&&buf[i]<='Z')
                        t=buf[i]-'A'+10;
                    sum=sum*16+t;
                }

            sprintf(str2, "%d", sum);
            strcat(buf,'-');
            strcat(buf,str2);
            strcat(buf,str3);




         send(tfd,buf,12,0);
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
    char s[BUF_SIZE];
      char str1[BUF_SIZE]="##";
    char str3[BUF_SIZE]=":17041129 杨宇晨";
    char str2[BUF_SIZE];
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
//    pthread_t id;
//    pthread_create(&id,NULL,recv_thread,&sockfd);
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
        else   { printf("receive from %d(socket): %s\n", sockfd, buf);	// 打印接收数据
                strcpy(s,buf);
//
                int i,t;             //t记录临时加的数
                int sum =0;
            for(i=0; s[i]; i++)
            {
                if(s[i]>='0'&&s[i]<='9')
                    t=s[i]-'0';       //当字符是0~9时保持原数不变
                if(s[i]>='a'&&s[i]<='z')
                    t=s[i]-'a'+10;
                if(s[i]>='A'&&s[i]<='Z')
                    t=s[i]-'A'+10;
                sum=sum*16+t;
            }
//            printf("%d",sum);

            sprintf(str2, "%d", sum);
            strcat(buf,"-");
            strcat(buf,str2);
            strcat(buf,str3);
            printf("%s",buf);


//
         send(sockfd,buf,strlen(buf),0);

        }
    }

    close(sockfd);	// 关闭socket
    return 0;
}


