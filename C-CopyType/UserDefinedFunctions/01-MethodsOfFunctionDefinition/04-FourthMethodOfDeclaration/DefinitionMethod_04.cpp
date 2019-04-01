
#include<stdio.h>

int main(int argc,char *argv[],char *envp[])
{
	//Function prototype
	int MyAddition(int,int);
	
	//variable 
	int a,b,result;
	
	//code
	
	printf("\n\n");
	printf("Enter Integer Value for A:");
	scanf("%d",&a);
	
	printf("Enter Integer Value for B:");
	scanf("%d",&b);
	
	result = MyAddition(a,b);
	printf("\n\n");
	printf("Sum of %d and %d = %d\n\n",a,b,result);
	return(0);
	
}

int MyAddition(int a,int b)
{
	//variable declarations
	int sum;
	
	//code
		
	sum=a+b;
	return(sum);
}
