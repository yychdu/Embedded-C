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
#include <arpa/inet.h>
#include<sys/time.h>
#define PORT			5566
#define MAX_QUE_CONN_NM	5
#define MAX_SOCK_FD		FD_SETSIZE
#define BUFFER_SIZE		1024
#define HOSTLEN 			256
unsigned int pr[99999999];
long long int sum=0;
void sushu(int N)
{
    unsigned int n=(unsigned int)sqrt(N+0.5);
    int i=0;
    int j=0;
    memset(pr,0,sizeof(pr));
    for(i=2;i<=n;i++)
    {
        if(pr[i]==0)
        {
            for(j=i*i;j<=N;j+=i)
            pr[j]=1;
        }
    }
}

int flag;
int main()
{
 long long a=89100000;
 long long b=90900000;
 long long c;
 long long m;
 long long n;
int j=0;
 int buf1[BUFFER_SIZE];
 int buf2[BUFFER_SIZE];
  int fs[BUFFER_SIZE];
//    clock_t start, finish;
//    double totaltime;
    struct  timeval  start;
    struct  timeval  end;
    long long timer;
    char strtime[25];
  char string1[25];
    char string2[25];
    char string3[252];
    char ip[25];
    struct sockaddr_in  server_sockaddr, client_sockaddr;
    int sin_size, count;
    fd_set inset, tmp_inset;
    int sockfd, client_fd, fd;
    char buf[BUFFER_SIZE];	// 接收、发送缓冲
    struct sockaddr_in scinf[100];	// 客户端地址池
    bzero((void *)scinf, sizeof(scinf));
    // 创建socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }
    // 初始化服务器地址结构体
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(server_sockaddr.sin_zero), 8);
    // 为bind设置地址复用
    int i = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
    if (bind(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    // 开始侦听客户端连接
    if (listen(sockfd, MAX_QUE_CONN_NM) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("Begin listening...\n");
    // 准备非阻塞方式连接多路客户端
    FD_ZERO(&inset);
    FD_SET(sockfd, &inset);

    srand(time(NULL));
     m=rand()%2000001-1000000;//-1000000-1000000
      n=rand()%10000000+90000000;//可能会过亿，越界   1-99999999
    if(sum==0)
    {
        sushu(n);
        if(m<=2){
            for(j=2; j<n; j++)
                if(!pr[j])
                    sum+=j;
        }
        else {
        for(j=m; j<n; j++)
            if(!pr[j])
                sum+=j;
                }
                sprintf(string3,"%lld",sum);
//              printf("%s\n",string3);
//       printf("sum=%lld\n",sum);
        }
   while (1)
    {

        tmp_inset = inset;
        sin_size = sizeof(struct sockaddr_in);
        memset(buf, 0, sizeof(buf));
        if (!(select(MAX_SOCK_FD, &tmp_inset, NULL, NULL, NULL) > 0))   //等待网络消息
        {
            perror("select");
            exit(1);
        }
        for (fd = 0; fd < MAX_SOCK_FD; ++fd)
        {

            if (FD_ISSET(fd, &tmp_inset) > 0)
            {




                if (fd == sockfd)    // 有客户端连接请求，accept之
                {
                    if ((client_fd = accept(sockfd, (struct sockaddr*)&client_sockaddr, &sin_size)) == -1)
                    {
                        perror("accept");
                        exit(1);
                    }
                    FD_SET(client_fd, &inset);
                    printf("New connection from %s\n", inet_ntoa(client_sockaddr.sin_addr));
                    strcpy(ip,inet_ntoa(client_sockaddr.sin_addr));
                    if (client_fd < 100 && client_fd >= 0)	// 新连接客户端记入地址池
                        memcpy((void *)(&scinf[client_fd]), (void *)&client_sockaddr, sin_size);


                }
                else    	// 有客户端数据
               {


                    if ((count = recv(fd, buf, BUFFER_SIZE, 0)) > 0)     	// 接收数据
                    {


                        if (fd >= 0 && fd < 100)
                           {
                           printf("Received from %s:%s\n", inet_ntoa(scinf[fd].sin_addr), buf);
                            }

                        if(strcmp(buf,"GET\n")==0||strcmp(buf,"GET")==0)
                        {
                                 gettimeofday(&start,NULL);

                            sprintf(string1, "%d",m);

                            strcpy(buf,string1);

                            strcat(buf,"-");

                                sprintf(string2, "%d", n);
                                strcat(buf,string2);
                                strcpy(fs,buf);

                        }

                           if(strlen(buf)>20)
                        {

//                            printf("buf=%s\nfs=%s\n",buf,fs);
                            if(strncmp(buf,fs,strlen(fs))==0)
                            {
//                          printf("OK\n");
                                strcat(fs,":");
                                strcat(fs,string3);
//                          printf("fs=%s\n",fs);
                           gettimeofday(&end,NULL);
                            timer = (1000000 * (end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec)/1000;
//                            printf("timer = %ld ms\n",timer);
                            sprintf(strtime,"%d",timer);

                                 if(timer>5000)
                                {
                                strcat(buf,"!TLL");
                                }
                                else if(strncmp(buf,fs,strlen(fs))==0)
                                {
                                    strcat(buf,"!OK");
                                    flag=1;
                                }

                                else{
                                strcat(buf,"!ERR");
                                }

                            }
                            strcat(ip,",");
                            strcat(ip,buf);

                            strcat(ip,",");
                            strcat(ip,strtime);
                            strcat(ip,"ms");
                            printf("%s\n",ip);
                             FILE* fp;
                                if ((fp = fopen("//home/fish/桌面/res.txt", "at+")) == NULL)
                                {
                                        printf("Cannot open file, press any key to exit!\n");
                                }
                                fputs(ip,fp);
                                fclose(fp);

                        }


                    if ((count = send(fd, buf, strlen(buf), 0)) == -1)   	// 回送数据
                        {
                            perror("send");
                            exit(1);
                        }
                    }
                    else   	// 无法读取数据，可能连接以断开
                    {
                        if (fd >= 0 && fd < 100)
                            printf("Client %s has left\n", inet_ntoa(scinf[fd].sin_addr));
                        memset((void *)(&scinf[client_fd]), 0, sin_size);
                        close(fd);
                        FD_CLR(fd, &inset);
                    }
                }
            }
        }
    }

    close(sockfd);
    return 0;
}








//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
//#include <string.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <netdb.h>
//#include <time.h>
//#include <string.h>
//#include <sys/ioctl.h>
//#include <arpa/inet.h>
//#define PORT			4321
//#define MAX_QUE_CONN_NM	5
//#define MAX_SOCK_FD		FD_SETSIZE
//#define BUFFER_SIZE		1024
//#define HOSTLEN 			256
//int main()
//{
//    struct sockaddr_in  server_sockaddr, client_sockaddr;
//    int sin_size, count;
//    fd_set inset, tmp_inset;
//    int sockfd, client_fd, fd;
//    char buf[BUFFER_SIZE];	// 接收、发送缓冲
//    struct sockaddr_in scinf[100];	// 客户端地址池
//    bzero((void *)scinf, sizeof(scinf));
//    // 创建socket
//    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//    {
//        perror("socket");
//        exit(1);
//    }
//    // 初始化服务器地址结构体
//    server_sockaddr.sin_family = AF_INET;
//    server_sockaddr.sin_port = htons(PORT);
//    server_sockaddr.sin_addr.s_addr = INADDR_ANY;
//    bzero(&(server_sockaddr.sin_zero), 8);
//    // 为bind设置地址复用
//    int i = 1;
//    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &i, sizeof(i));
//    if (bind(sockfd, (struct sockaddr *)&server_sockaddr, sizeof(struct sockaddr)) == -1)
//    {
//        perror("bind");
//        exit(1);
//    }
//    // 开始侦听客户端连接
//    if (listen(sockfd, MAX_QUE_CONN_NM) == -1)
//    {
//        perror("listen");
//        exit(1);
//    }
//    printf("Begin listening...\n");
//    // 准备非阻塞方式连接多路客户端
//    FD_ZERO(&inset);
//    FD_SET(sockfd, &inset);
//
//    srand(time(NULL));
//   while (1)
//    {
//        tmp_inset = inset;
//        sin_size = sizeof(struct sockaddr_in);
//        memset(buf, 0, sizeof(buf));
//        if (!(select(MAX_SOCK_FD, &tmp_inset, NULL, NULL, NULL) > 0))   //等待网络消息
//        {
//            perror("select");
//            exit(1);
//        }
//        for (fd = 0; fd < MAX_SOCK_FD; ++fd)
//        {
//            if (FD_ISSET(fd, &tmp_inset) > 0)
//            {
//                if (fd == sockfd)    // 有客户端连接请求，accept之
//                {
//                    if ((client_fd = accept(sockfd, (struct sockaddr*)&client_sockaddr, &sin_size)) == -1)
//                    {
//                        perror("accept");
//                        exit(1);
//                    }
//                    FD_SET(client_fd, &inset);
//                    printf("New connection from %s\n", inet_ntoa(client_sockaddr.sin_addr));
//                    if (client_fd < 100 && client_fd >= 0)	// 新连接客户端记入地址池
//                        memcpy((void *)(&scinf[client_fd]), (void *)&client_sockaddr, sin_size);
//                }
//                else    	// 有客户端数据
//                {
//                    if ((count = recv(fd, buf, BUFFER_SIZE, 0)) > 0)     	// 接收数据
//                    {
//                        if (fd >= 0 && fd < 100)
//                            printf("Received from %s:\t%s\n", inet_ntoa(scinf[fd].sin_addr), buf);
//
//
//                        if(strcmp(buf,"GET")==0 || strcmp(buf,"GET\n")==0)
//                        {
//                            buf[0]=buf[1]='#';
//                            int i;
//                            for(i=0;i<10;++i)
//                            {
//                                buf[2+i]=' '+(rand() % ('z'-' '))+1;
//                                if(buf[2+i]=='#')
//                                --i;
//                            }
//
//
//
//
//                        }
//
//                        if ((count = send(fd, buf, strlen(buf), 0)) == -1)   	// 回送数据
//                        {
//                            perror("send");
//                            exit(1);
//                        }
//                    }
//                    else   	// 无法读取数据，可能连接以断开
//                    {
//                        if (fd >= 0 && fd < 100)
//                            printf("Client %s has left\n", inet_ntoa(scinf[fd].sin_addr));
//                        memset((void *)(&scinf[client_fd]), 0, sin_size);
//                        close(fd);
//                        FD_CLR(fd, &inset);
//                    }
//                }
//            }
//        }
//    }
//
//    close(sockfd);
//    return 0;
//}
