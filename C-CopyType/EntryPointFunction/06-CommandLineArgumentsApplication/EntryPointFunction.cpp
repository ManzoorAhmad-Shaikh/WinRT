#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
int main(int argc,char *argv[],char *envp[])
{
	int i,num,sum=0;
	
	//code
	
	printf("\n\n");
	printf("Sum of All Integer Command line Argument is :\n\n");
	
	for(i=1;i<argc;i++)
	{
		num=atoi(argv[i]);
		sum=sum+num;
	}
	
	printf("Sum = %d\n\n",sum);
}