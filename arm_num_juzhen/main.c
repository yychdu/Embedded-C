#include <stdio.h>
#include <stdlib.h>
//数字矩阵
int main()
{
    int N=0;
    printf("input num N(0<N<10):");
    scanf("%d",&N);
///////////////////////////////////////

    int i,j,t;
    for(i=0;i<N;i++){
    t=N*N-i;
     for(j=0;j<N;j++)
      printf("%3d ",t-N*j);
           printf("\n");
}
 ////////////////////////////////////////
 printf("\n");

 //N奇数
 if(N%2==1){
     int i,j,t;
    for(i=0;i<N;i++){    //i行　０行开始
    t=N*N-i*N;    //每行最大值

         if((i+1)%2==1) { //奇数行   从大到小
     for(j=0;j<N;j++)
           printf("%3d ",t-j);

           }
    else{    //偶数行  从小到大
              for(j=N-1;j>=0;j--)
           printf("%3d ",t-j);
           }
             printf("\n");
     }
}

//N偶数
else{
     int i,j,t;
    for(i=0;i<N;i++){
    t=N*N-i*N;    //每行最大值

         if((i+1)%2==0) { //偶数行
     for(j=0;j<N;j++)
           printf("%3d ",t-j);

           }
    else{    //奇数行
              for(j=N-1;j>=0;j--)
           printf("%3d ",t-j);
           }
             printf("\n");
     }
}
///////////////////////////////////////
  return 0;

}


