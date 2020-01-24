#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <signal.h>
int bsend = 1;
void sigusr(int sig)
{
    if(SIGUSR1 == sig)
   { bsend = 0;
    printf("stopped!\n");
    }
    else if(SIGUSR2 == sig)
   { bsend = 1;
    printf("continue...\n");}
}
pid_t findpid(const char *pname)
{
  char buf[1024];
  int id=-1;
  FILE *pp;
  if (NULL != pname && strlen(pname)>0)
  {
    sprintf(buf,"pidof %s",pname);
    if((pp= popen(buf,"r"))!=NULL)
    {
        if (fgets(buf,sizeof(buf),pp))
           id = atoi(buf);
           pclose(pp);
    }

  }
   return (pid_t)id;
}
int main()
{
    char buf[80];
    int fd = open("/home/fish/mypipe", O_WRONLY);
    if (fd < 0)
    {
        printf("Error opening pipe.\n");
        exit(1);
    }
    signal(SIGUSR1,sigusr);
    signal(SIGUSR2,sigusr);
    srand(time(0));
    while(1)
    {
        if(bsend)
        {
           int n= rand() %101;
        sprintf(buf,"%d\n",n);
         write(fd, buf, strlen(buf));
        }

        usleep(100000) ;
    }

    close(fd);
    return 0;
    }
