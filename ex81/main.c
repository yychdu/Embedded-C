#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
char led1[] = "****";
char led0[] = "oooo";
int sta = 0;
void sigusr(int sig){
    printf("\nsigusr1 signal received!\n");
    signal(SIGUSR1, sigusr);
    sta = !sta;
}
int main()
{
    signal(SIGUSR1,sigusr);
    while(1){
            if(sta)
                printf("%s\n",led1);
            else
                printf("%s\n",led0);
        usleep(100000);
        }
    sleep(1);
}
