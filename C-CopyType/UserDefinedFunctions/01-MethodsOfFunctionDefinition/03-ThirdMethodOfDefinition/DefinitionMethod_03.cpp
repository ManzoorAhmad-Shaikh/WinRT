#include<stdio.h>

int main(int argc,char *argv[],char *envp[])
{
	//Function prototype
	void MyAddition(int,int);
	
	//variable 
	int a,b;
	
	//code
	
	printf("\n\n");
	printf("Enter Integer Value for A:");
	scanf("%d",&a);
	
	printf("Enter Integer Value for B:");
	scanf("%d",&b);
	
	MyAddition(a,b);
	return(0);
	
}

void MyAddition(int a,int b)
{
	//variable declarations
	int sum;
	
	//code
		
	sum=a+b;
	printf("\n\n");
	printf("Sum of %d and %d = %d\n\n",a,b,sum);
}

