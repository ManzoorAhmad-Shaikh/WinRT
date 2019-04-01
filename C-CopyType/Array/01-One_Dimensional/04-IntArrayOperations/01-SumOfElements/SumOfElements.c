#include<stdio.h>

#define NUM_ELEMENTS 10

int main(void)
{
	//var declaration
	int iArray[NUM_ELEMENTS];
	int i,num,sum=0;
	
	printf("\n\n Enter Integer Elements for Array : ");
	for(i=0;i<NUM_ELEMENTS;i++)
	{
		scanf("%d",&num);
		iArray[i]=num;
	}
	
	for(i=0;i<NUM_ELEMENTS;i++)
	{
		sum=sum+iArray[i];
	}
	printf("\n\n \t Sum of all Elements of Array = '%d'\n ",sum);

return(0);
}
