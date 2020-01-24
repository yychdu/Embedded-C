#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

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
    int count = 1;
    char buf[80];
    if((mkfifo("/home/fish/mypipe", 0666) < 0) && (errno != EEXIST))
    {
        perror("mkfifo error.\n");
        exit(1);
    }
    int fd = open("/home/fish/mypipe", O_RDONLY);
    if (fd < 0)
    {
        printf("Error in fdopen.\n");
        exit(1);
    }
    int cnt = 0;
    while (1)
    {
        if ((count = read(fd, buf, 80)) > 0)
        {
           int n=atoi(buf);
           printf("%d\n",n);
           if (n>50)
              ++cnt;
         else
              cnt = 0;
         if ( cnt>=3 )
         {
            cnt = 0;
            pid_t pid = findpid("ex64");
            if(pid>0);
            {
                kill(pid,SIGUSR1);
                printf("find 3 nums >50.\n");
                usleep(5000000);
                kill(pid,SIGUSR2);

            }

         }

        }
    }
    close(fd);
    return 0;
}
