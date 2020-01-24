#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include<math.h>
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
unsigned int pr[99999999];
unsigned int luc[99999999];
void sushu(int N)
{
    unsigned int n=(unsigned int)sqrt(N+0.5);
    int i=0;
    int j=0;
    memset(pr,0,sizeof(pr));
    for(i=2; i<=n; i++)
    {
        if(pr[i]==0)
        {
            for(j=i*i; j<=N; j+=i)
                pr[j]=1;
        }
    }
}
//B 设计一个程序，读取用户输入的一个整数 N（N > 1000, N < 10000000），输
//出与其最接近的一个幸运素数，如用户输入 2017，程序输出 1999
int main()
{
    sushu(10000000);

    int i,j,sum=0,m=0,p,data,s=0,k=0;
    int lucd[170];
    int cha[170];
    char buf[20];
    char buff[20];
    printf("input:\n");
    scanf("%d",&data);
    if(data<=1000||data>=10000000)
    {
    printf("eRror");
    return 0;
    }
    for(p=1000; p<10000000; p++)
    {
        sprintf(buf,"%d",p);
        for(i = 0; i < strlen(buf)-1; i++)

        {

            for(j = 0; j < strlen(buf)-i-1; j++)

            {

                if(buf[j]>buf[j + 1])

                {

                    int temp = buf[j];

                    buf[j] = buf[j + 1];

                    buf[j + 1] = temp;

                }

//        if(sum==1)
            }
        }
        if(buf[0]!=buf[1])
        {
            for(i=1; i<strlen(buf); i++)
            {
                if(buf[1]==buf[i])
                    sum++;
            }
        }
        else if(buf[strlen(buf)-1]!=buf[strlen(buf)-2])
        {
            for(i=strlen(buf)-2; i>=0; i--)
            {
                if(buf[strlen(buf)-2]==buf[i])
                    sum++;
            }
        }
        else sum=-1;

        if(sum==strlen(buf)-1)
        {
            if(!pr[p])
                luc[p]=1;
            else
            {
                luc[p]=0;
            }
        }
        else    luc[p]=0;
        sum=0;

        if(luc[p])
        {
        printf("%d ",p);
        lucd[s++]=p;
        }

    }
//    printf("%d",lucd[170]);
    for(i=0;i<170;i++)
    {
    cha[i]=fabs(data-lucd[i]);
    }
    for(i=0;i<170;i++)
    {
        if(cha[k]>cha[i])k=i;
    }
    printf("最近：%d\n",lucd[k]);
//    printf("sum=%d,buff=%s\n",sum,buff);
    return 0;
}
