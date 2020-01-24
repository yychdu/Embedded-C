//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
//#include <string.h>
//#include <netdb.h>
//#include <sys/types.h>
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <errno.h>
//#include <string.h>
//#include <netdb.h>
//
//#include <pthread.h>
//#include <netinet/in.h>
//#include <sys/socket.h>
//#define PORT	5566
//#define BUF_SIZE	1024
//#include<stdbool.h>
//
//unsigned int pr[99999999];
//void sushu(int N)
//{
//    unsigned int n=(unsigned int)sqrt(N+0.5);
//    int i=0;
//    int j=0;
//    memset(pr,0,sizeof(pr));
//    for(i=2;i<=n;i++)
//    {
//        if(pr[i]==0)
//        {
//            for(j=i*i;j<=N;j+=i)
//            pr[j]=1;
//        }
//    }
//}
//
//int main(int argc, char *argv[])
//{
//    long long int m,n,i,j,sum=0;
//    int sockfd, sendbytes,recvbytes,sendfin=1;
//    char buf[BUF_SIZE]="GET\n";
////    char buf[BUF_SIZE];
//    struct hostent *host;
//    struct sockaddr_in serv_addr;
//    char buf1[BUF_SIZE];
//    char buf2[BUF_SIZE];
//    char buf3[BUF_SIZE];
//    char buff[BUF_SIZE];
//    if (argc < 2)   	// 检查程序参数个数
//    {
//        printf("USAGE: ./tclient Hostname(or ip address)\n");
//        exit(1);
//    }
//
//    // 检查程序参数指定的服务器地址
//    if ((host = gethostbyname(argv[1])) == NULL)
//    {
//        perror("gethostbyname");
//        exit(1);
//    }
//
//    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) // 创建一个流式socket
//    {
//        perror("socket");
//        exit(1);
//    }
//
//    // 初始化serv_addr结构体变量
//    serv_addr.sin_family = AF_INET;
//    serv_addr.sin_port = htons(PORT);
//    serv_addr.sin_addr = *((struct in_addr *)host->h_addr);
//    bzero(&(serv_addr.sin_zero), 8);
//
//    // 连接服务器
//    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1)
//    {
//        perror("connect");
//        exit(1);
//    }
////    pthread_t id;
////    pthread_create(&id,NULL,recv_thread,&sockfd);
//    // 显示连接信息
//    printf("connect to server %s...\n", argv[1]);
//    sushu(100000000);
//    while (1)     	// 循环发送、接收服务器信息
//    {
////        bzero(buf, sizeof(buf));	// 清空缓冲
//        if(sendfin)
//        {
//            if ((sendbytes = send(sockfd, buf, strlen(buf), 0)) == -1)    	// 是否发送成功
//            {
//                perror("send");
//                exit(1);
//            }
//            sendfin=0;
//        }
//        int p=1;
//      bzero(buf, sizeof(buf));	// 清空缓冲
//        if ((recvbytes = recv(sockfd, buf, BUF_SIZE, 0)) == -1)   	// 等待接收数据
//        {
//           perror("recv");
//           exit(1);
//       }
//        else   {
//        printf("receive from %d(socket):%s\n", sockfd, buf);	// 打印接收数据
//        if(buf[0]!='-')
//        {
//            for(i=0; i<BUF_SIZE; i++)
//            {
//                if(buf[i]!='-')
//                {
//                    buf1[i]=buf[i];
//                }
//                else break;
//            }
//        }
//        else{
//            for(i=1; i<BUF_SIZE; i++)
//            {
//
//                if(buf[i]!='-')
//                {
//                    p++;
//                }
//                else break;
//            }
//            strncpy(buf1,buf,p);
//        }
//
//
//
//            if(buf[0]!='-')
//            {
//                for(i=strlen(buf1)+1; i<BUF_SIZE; i++)
//                {
//                    if(buf[i]!='\0')
//                        buf2[j++]=buf[i];
//                    else break;
//
//                }
//            }
//
//            else{
//
//            for(i=strlen(buf1)+1; i<BUF_SIZE; i++)
//                {
//                    if(buf[i]!='\0')
//                        buf2[j++]=buf[i];
//                    else break;
//
//                }
//            }
//
//
//        m=atoi(buf1);
//        n=atoi(buf2);
//
//      if(m<2){
//            for(j=2; j<n; j++)
//                if(!pr[j])
//                    sum+=j;
//        }
//        else {
////        if(m==0)
////        {
////            sum=sum-1;
////        }
//        for(j=m; j<n; j++)
//            if(!pr[j])
//                sum+=j;
//                }
//        sprintf(buff, "%lld", sum);
//        strcpy(buf3,buf1);
//        strcat(buf3,"-");
//        strcat(buf3,buf2);
//        strcat(buf3,":");
//        strcat(buf3,buff);
//        strcpy(buf,buf3);
////    printf("m=%s,n=%s,buf3=%s\n",buf1,buf2,buf3);
////        printf("%lld  %lld:%lld\n",m,n,sum);
//        printf("回送：%s\n",buf);
//        send(sockfd,buf,strlen(buf),0);
//        break;
//}
//
//    }
//
//
//
//
//
//    close(sockfd);	// 关闭socket
//    return 0;
//}
//
//
//




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
#define PORT	4321
#define BUF_SIZE	1024

void* recv_thread(void *d)
{

    char buf[BUF_SIZE];
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
                        int i = 0;

                        int j = 0;

           for(i = 0; i < 10; i++)

            {

           for(j = 2; j < 12-i-1; j++)

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
