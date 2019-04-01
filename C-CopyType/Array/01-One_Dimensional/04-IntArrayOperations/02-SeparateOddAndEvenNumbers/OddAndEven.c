#include<stdio.h>

#define NUM_ELEMENTS 10

int main(void)
{
	int iArray[NUM_ELEMENTS];
	int i,num,sum=0;
	
	//code
	printf("\n\n Enter Integers Elements for Array : ");
	for(i=0;i<NUM_ELEMENTS;i++)
	{
		scanf("%d",&num);
		iArray[i]=num;
	}
	
	printf("\n\n Even Numbers Amongst the Array Elements Are : \n");
	for(i=0;i<NUM_ELEMENTS;i++)
	{
		if((iArray[i]%2)==0)
		printf("\t %d \n",iArray[i]);
	}
	
	printf("\n\n ODD Numbers Amongst the Array Elements Are : \n");
	for(i=0;i<NUM_ELEMENTS;i++)
	{
		if((iArray[i]%2)!=0)
		printf("\t %d \n",iArray[i]);
	}	
	
	return(0);
}
