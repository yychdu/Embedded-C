#include <stdio.h>
#include <stdlib.h>
#define IOCTL_LED_ON    1
#define IOCTL_LED_OFF   0
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<pthread.h>

int led_run=1;
int led_speed =1;
int main_run=1;
void* mythread(void *d)
{
    char str[100];
    while(main_run)
    {
        if(fgets(str,100,stdin))
        {
        if(strstr(str,"start"))
            led_run=1;
        else if(strstr(str,"stop"))
            led_run=0;
        else if(strstr(str,"speed")==str)
        {
            led_speed=atoi(str+5);
            if(led_speed<1)
                led_speed=1;
                if(led_speed>9)
                led_speed=9;
        }
            else if(strcmp(str,"quit\n")==0)
                main_run=0;
        }

    }
    return 0;
}



int main(int argc,char** argv)
{
    printf("Hello leds!\n");
    int fd=open("/dev/leds",0);
    if(fd>0){
        int i;

    pthread_t id;
    pthread_create(&id, NULL, mythread, 0);
        while(main_run)
        {
            if(led_run)
            {
                for(i=0; i<6; i++)
                {
                    ioctl (fd, IOCTL_LED_OFF, 0);
                    ioctl (fd, IOCTL_LED_OFF, 1);
                    ioctl (fd, IOCTL_LED_OFF, 2);
                    ioctl (fd, IOCTL_LED_OFF, 3);
                    ioctl (fd, IOCTL_LED_ON,  (i>=4)?6-i :i);
                    usleep(100000*(10-led_speed));


                }
            }
            else
                usleep(100000);

    }
    close(fd);

    }
    return 0;
}
