//B 在一个 ARM Linux 程序，打印出一千万以内所有的回文素数（一万以上且是回
//文样式的素数，如 12421、16661、9980899 这种左右对称的素数），并打印一千
//万以内所有的素数个数。

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
    for(i=2; i<=n; i++)
    {
        if(pr[i]==0)
        {
            for(j=i*i; j<=N; j+=i)
                pr[j]=1;
        }
    }
}
int main()
{

    int c,hw=0,ss,sum=0,i;
    char buf[100];
    sushu(10000000);
//    printf("input:\n");


    for(c=10000; c<=10000000; c++)
    {
        if(pr[c])
//    printf("%d不是素数\n",c);
            ss=0;
        else
//    printf("%d是素数\n",c);
            ss=1;
    if(ss==1){
//         memset(buf, 0, 128);
        sprintf(buf, "%d", c);
        if(strlen(buf)%2==0)
            hw=0;
        else
        {

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


        if(hw==1){
        printf("%d ",c);
        hw=0;
        }

                }
    }
    for(i=2; i<10000000; i++)
    {
        if(!pr[i])
            sum++;
    }
    printf("10000000内共有%d个素数",sum);
    return 0;
}
