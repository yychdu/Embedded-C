

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <pthread.h>

void pl(void)
{
    char p[20],str[20], sz[20], zm[20], qt[20];
    int i = 0, n, a, b, c,temp;
    a = b = c = 0;
    printf("Please input string:");
    fgets(str, 20, stdin);

    n = strlen(str);
    while(i<n)
    {
        if (str[i]>='0'&&str[i]<='9')
            sz[a++] = str[i];
        else if(str[i]>='a'&&str[i]<='z'||str[i]>='A'&&str[i]<='Z')
//            zm[b++] = str[i];
            {
                if(str[i]>='a'&&str[i]<='z')
                    zm[b++] = str[i]-32;
                else zm[b++] = str[i];
            }

        else
            qt[c++] = str[i];
        i++;
    }
    sz[a] = '\0';
    zm[b] = '\0';
    qt[c] = '\0';//末尾添加串结束标志；

    puts(sz); //输出所输入的数字字符；
    puts(zm); //输出所输入的字母字符；

    puts(qt); //输出所输入的其他字符

    strcat(sz,zm);
    puts(sz);



        int j =0;

        for(i = 0; i < strlen(sz); i++)

        {

            for(j = 0; j < strlen(sz)-i-1; j++)

            {

                if(sz[j]>sz[j + 1])

                {

                    int temp = sz[j];

                    sz[j] =sz[j + 1];

                    sz[j + 1] = temp;

                }

            }

        }
        puts(sz);


}

int open_port(int comport) // 打开串口设备
{
    char str[20];
    int fd = -1;
    if (comport > 0)
    {
        sprintf(str, "/dev/ttyS%d", comport - 1);
        fd = open(str,
                  O_RDWR|O_NOCTTY|O_NDELAY);
        if (-1 == fd)
        {
            perror("Can't Open Serial Port");
            return(-1);
        }
    }
    return fd;
}
int set_opt(int fd,int nSpeed, int nBits, char nEvent, int nStop)   // 配置串口参数
{
    struct termios newtio,oldtio;
    if ( tcgetattr( fd,&oldtio) != 0)
    {
        perror("SetupSerial 1");
        return -1;
    }
    bzero( &newtio, sizeof( newtio ) );
    newtio.c_cflag |= CLOCAL | CREAD;
    newtio.c_cflag &= ~CSIZE;
    switch( nBits )
    {
    case 7:
        newtio.c_cflag |= CS7;
        break;
    case 8:
        newtio.c_cflag |= CS8;
        break;
    }
    switch( nEvent )
    {
    case 'O':
        newtio.c_cflag |= PARENB | PARODD;
        newtio.c_iflag |= (INPCK | ISTRIP);
        break;
    case 'E':
        newtio.c_iflag |= (INPCK | ISTRIP);
        newtio.c_cflag |= PARENB;
        newtio.c_cflag &= ~PARODD;
        break;
    case 'N':
        newtio.c_cflag &= ~PARENB;
        break;
    }
    switch( nSpeed )
    {
    default:
    case 9600:
        cfsetispeed(&newtio, B9600);
        cfsetospeed(&newtio, B9600);
        break;
    case 115200:
        cfsetispeed(&newtio, B115200);
        cfsetospeed(&newtio, B115200);
        break;
    }
    if( nStop == 1 ) newtio.c_cflag &= ~CSTOPB;
    else if ( nStop == 2 ) newtio.c_cflag |= CSTOPB;
    newtio.c_cc[VTIME] = 0;
    newtio.c_cc[VMIN] = 0;
    tcflush(fd,TCIFLUSH);
    if((tcsetattr(fd,TCSANOW,&newtio))!=0)
    {
        perror("com set error");
        return -1;
    }
    printf("serial set done!\n");
    return 0;
}

void* serial_lsd(void *d)   // 线程函数，串口输出流水灯
{
    int i = 0;
    int tfd = *(int *)d;
    if (tfd > 0)
    {
        while (1)
        {
            char buf[20], str[] = "oooooooooo";
            if (i < 10) str[i++] = '*';
            else str[19 - i++] = '*';
            if((i%=20) == 0){
                i == 0;
            }
            sprintf(buf, "%s\r\n", str);
            write(tfd, buf, strlen(buf));
            usleep(100000); // 延时100ms
        }
    }
    return 0;
}
int main(void)
{

    char p[20],str[20], sz[100], zm[100], qt[100];
    int i = 0, n, a, b, c,temp;
    a = b = c = 0;
    int fd, nread;
    char buff[128] = "Hello\n";
    fd_set rd;
    if((fd = open_port(2)) < 0)
    {
        perror("open_port error");
        return -1;
    }
    if((i = set_opt(fd,9600,8,'N',1))<0)
    {
        perror("set_opt error");
        return -1;
    }

//    pthread_t id;
//    pthread_create(&id, NULL, serial_lsd, &fd);
    FD_ZERO(&rd);
    FD_SET(fd,&rd);
    while(FD_ISSET(fd,&rd))
    {
        if(select(fd+1,&rd,NULL,NULL,NULL)<0) perror("select");
        else
        {
            memset(buff, 0, sizeof(buff));
//            memset(sz, 0, sizeof(sz));
            while((nread = read(fd, buff, 128))>0)
            {
                a=0;b=0;c=0;i=0;
                printf("nread=%d,%s\n",nread,buff);
                n = strlen(buff);
                while(i<n)
                {
                    if (buff[i]>='0'&&buff[i]<='9')
                        sz[a++] = buff[i];
                    else if(buff[i]>='a'&&buff[i]<='z'||buff[i]>='A'&&buff[i]<='Z')
//            zm[b++] = buff[i];
                    {
                        if(buff[i]>='a'&&buff[i]<='z')
                            zm[b++] = buff[i]-32;
                        else zm[b++] = buff[i];
                    }

                    else
                        qt[c++] = buff[i];
                    i++;
                }
                sz[a] = '\0';
                zm[b] = '\0';
                qt[c] = '\0';//末尾添加串结束标志；

//                puts(sz); //输出所输入的数字字符；
//                puts(zm); //输出所输入的字母字符；

//                puts(qt); //输出所输入的其他字符

                strcat(sz,zm);
//                puts(sz);
                  int j =0;

        for(i = 0; i < strlen(sz); i++)

        {

            for(j = 0; j < strlen(sz)-i-1; j++)

            {

                if(sz[j]>sz[j + 1])

                {

                    int temp = sz[j];

                    sz[j] =sz[j + 1];

                    sz[j + 1] = temp;

                }

            }

        }
        puts(sz);
                strcpy(buff,sz);
                write(fd, buff, strlen(buff)); // 回送接收数据
//                memset(sz, 0, 128);
//            return 0;
            }
        }
    }
    close(fd);
    return 0;
}


