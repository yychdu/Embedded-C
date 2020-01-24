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
    int fd, nread, i;
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
            memset(buff, 0, 128);
            while((nread = read(fd, buff, 128))>0)
            {
                printf("nread=%d,%s\n",nread,buff);

                write(fd, buff, strlen(buff)); // 回送接收数据
            }
        }
    }
    close(fd);
    return 0;
}
