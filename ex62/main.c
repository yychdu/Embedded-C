#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
int i = 1;
void sigalrm_fn(int sig){
    i=0;
    printf("alarm!\n");
    alarm(2);
}
void sig_get(void){
    signal(SIGALRM,sigalrm_fn);
    alarm(2);
    while(i)usleep(1000);
}
pid_t findpid(const char *pname)
{
    char buf[1024];
    int id=-1;
    FILE *pp;
    if(NULL!=pname&&strlen(pname)>0)
    {
        sprintf(buf,"pidof %s",pname);
        if(pp=popen(buf,"r"))
        {
            if (fgets(buf,sizeof(buf),pp)!=NULL)id=atoi(buf);
            pclose(pp);
        }
    }
return(pid_t)id;
}
int main(){
    while(1){



                pid_t pid = findpid("ex81");
                if(pid >0){
                    kill(pid,SIGUSR1);
                    printf("changed\n");
                    i = 1;
                    sig_get();
                }
                else{
                    printf("send SIGUSR1 signale to process!\n");

                }

    }

    return 0;
}

