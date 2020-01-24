#include <stdio.h>
#include <stdlib.h>
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
    int c,hw=0,sum=0,i;
    char buf[10];
    sushu(10000000);
    printf("input:\n");
    scanf("%d",&c);
    for(i=2;i<c;i++)
    {
        if(!pr[i])
            sum++;
    }
    printf("%d内共有%d个素数",c,sum);
    return 0;
}
