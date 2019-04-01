#include<stdio.h>	

#define INT_ARRAY_NUM_ELEMENTS 5
#define FLOAT_ARRAY_NUM_ELEMENTS 3
#define CHAR_ARRAY_NUM_ELEMENTS 15

int main(void)
{
	int iArray[INT_ARRAY_NUM_ELEMENTS];
	float fArray[FLOAT_ARRAY_NUM_ELEMENTS];
	char cArray[CHAR_ARRAY_NUM_ELEMENTS];
	
	int i,num;
	
	
	printf("\n");
	printf("\n Enter Elements for 'Integer' Array : \n");
	for(i=0;i<INT_ARRAY_NUM_ELEMENTS;i++)
	{
		scanf("%d",&iArray[i]);
	}

	printf("\n\n Enter Elements for 'Float' Array : ");
	for(i=0;i<FLOAT_ARRAY_NUM_ELEMENTS;i++)
	{
		scanf("%f",&fArray[i]);
	}	
	
	printf("\n\n Enter Elements for 'Character' Array : ");
	for(i=0;i<CHAR_ARRAY_NUM_ELEMENTS;i++)
	{
		scanf("%c \n",&cArray[i]);
	}
	
	//*******PRINTING ELEMENTS
	
	printf("\n\n Integer Elements Entered by You : \n");
	for(i=0;i<INT_ARRAY_NUM_ELEMENTS;i++)
	{
		printf("\t %d \n",iArray[i]);
	}

	printf("\n\n Float Elements Entered by You : \n");
	for(i=0;i<FLOAT_ARRAY_NUM_ELEMENTS;i++)
	{
		printf("\t %f \n",fArray[i]);
	}		
	
	printf("\n\n Character Elements Entered by You : \n");
	for(i=0;i<CHAR_ARRAY_NUM_ELEMENTS;i++)
	{
		printf("\t %c \n",cArray[i]);
	}
	
	
	return(0);
}
