#include<stdio.h>

int main(int argc,char *argv[],char *envp[])
{
	//Function prototype
	void MyAddition(void);
	
	//code
	MyAddition();
	return(0);
	
}

void MyAddition(void)
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
	printf("\n\n");
	printf("Sum of %d and %d = %d\n\n",a,b,sum);
}
