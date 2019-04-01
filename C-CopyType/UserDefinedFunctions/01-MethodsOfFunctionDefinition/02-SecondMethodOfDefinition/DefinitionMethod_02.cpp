#include<stdio.h>

int main(int argc,char *argv[],char *envp[])
{
	//Function prototype
	int MyAddition(void);
	
	//variable 
	int result;
	
	//code
	result = MyAddition();
	printf("\n\n");
	printf("Sum = %d\n\n",result);
	return(0);
	
}

int MyAddition(void)
{
	//variable declarations
	int a,b,sum;
	
	//code
	
	printf("\n\n");
	printf("Enter Integer Value for A:");
	scanf("%d",&a);
	
	printf("Enter Integer Value for B:");
	scanf("%d",&b);
	
	sum=a+b;
	return(sum);
}

