#include <stdio.h>
#include <stdlib.h>
#include<string.h>
unsigned int pr[99999999];
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
int main()
{

    int c,hw=0,ss;
    char buf[10];
    sushu(10000000);
    printf("input:\n");
    scanf("%d",&c);
        if(c==1){
        printf("%d is loop，but not a prime number；",c);
        return 0;
        }
    sprintf(buf, "%d", c);
    if(strlen(buf)%2==0)
    hw=0;
    else{
        if(strlen(buf)==1)
        hw=1;
        if(strlen(buf)==3)
            {
            if(buf[0]==buf[2])
                hw=1;
                }
        if(strlen(buf)==5)
        {
             if(buf[0]==buf[strlen(buf)-1])
                if(buf[1]==buf[strlen(buf)-2])
                hw=1;
        }
        if(strlen(buf)==7)
            {
                if(buf[0]==buf[strlen(buf)-1])
                if(buf[1]==buf[strlen(buf)-2])
                if(buf[2]==buf[strlen(buf)-3])
                hw=1;
            }


    }
    if(pr[c])
//    printf("%d不是素数\n",c);
    ss=0;
    else
//    printf("%d是素数\n",c);
    ss=1;
    if(ss==0&&hw==0)
        printf("%d  is no a loop lucky prime number；\n",c);
    if(ss==1&&hw==0)
        printf("%d is a prime number， but not loop；",c);
    if(ss==0&&hw==1)
    printf("%d is loop，but not a  lucky prime number；",c);
    if(ss==1&&hw==1)
    printf("%d is a loop lucky prime number",c);

    return 0;
}
