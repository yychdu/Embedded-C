#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
	int i,j,k,n,h,m;
	scanf("%d",&n);
	if(n%2!=0){

		// ////中间没空的

	for(i=n,h=n+2,m=1;i>0;i-=2,h--,m++)
	{
		if(i==n)
		{
			for(j=2*n-1;j>0;j--)
			if(j%2)
				printf("*");
			else
				printf(" ");
		}
		else
		{
			printf("*");
			for(k=1;k<2*n-2;k++)
				printf(" ");
			printf("*");
		}

		for(k=h;k>0;k--)
			printf(" ");
		for(j=0;j<2*m-1;j++){
			if(j%2==0)
				printf("*");
			else
				printf(" ");
		}

			printf("\n");

	}



		//for(j=n-i;j>0;j--)
		//	printf(" ");

	for(i=i+4,h=h+2,m=m-2;i<=n;i+=2,h++,m--)
	{
		if(i==n)
		{
			for(j=2*n-1;j>0;j--)
			if(j%2)
				printf("*");
			else
				printf(" ");
		}
		else
		{
			printf("*");
			for(k=1;k<2*n-2;k++)
				printf(" ");
			printf("*");
		}
		for(k=h;k>0;k--)
			printf(" ");
		for(j=0;j<2*m-1;j++){
			if(j%2==0)
				printf("*");
			else
				printf(" ");
		}

		printf("\n");

	}

	}
	else{
		for(i=n,h=n+2,m=1;i>0;i-=2,h--,m++)
		{
			if(i==n)
			{
				for(j=2*n-1;j>0;j--)
				if(j%2)
					printf("*");
				else
					printf(" ");
			}
			else
			{
				printf("*");
				for(k=1;k<2*n-2;k++)
					printf(" ");
				printf("*");
			}

			for(k=h;k>0;k--)
				printf(" ");
			for(j=0;j<2*m-1;j++){
				if(j%2==0)
					printf("*");
				else
					printf(" ");
			}

				printf("\n");

		}



			//for(j=n-i;j>0;j--)
			//	printf(" ");

		for(i=i+2,h=h+1,m=m-1;i<=n;i+=2,h++,m--)
		{
			if(i==n)
			{
				for(j=2*n-1;j>0;j--)
				if(j%2)
					printf("*");
				else
					printf(" ");
			}
			else
			{
				printf("*");
				for(k=1;k<2*n-2;k++)
					printf(" ");
				printf("*");
			}
			for(k=h;k>0;k--)
				printf(" ");
			for(j=0;j<2*m-1;j++){
				if(j%2==0)
					printf("*");
				else
					printf(" ");
			}

			printf("\n");

		}
	}

	return 0;

}
