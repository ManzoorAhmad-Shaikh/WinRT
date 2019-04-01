#include<stdio.h>

int main(int argc,char *argv[],char *envp[])
{
	int i;
	//code
	printf("\n\n");
	printf("Hello World !!!\n");
	printf("Number of Command Line Arguments = %d\n\n",argc);
	
	for(i=0;i<argc;i++)
	{
		printf("Command Line Argument Number %d =%s \n",(i+1),argv[i]);
	}
	printf("\n\n");
	
	printf("First 20 Environmental Variables passed to this program are: \n\n");
	
	for(i=0;i<20;i++)
	{
		printf("Command Line Argument Number %d =%s \n",(i+1),envp[i]);
	}
	printf("\n\n");
	
	return(0);
}

