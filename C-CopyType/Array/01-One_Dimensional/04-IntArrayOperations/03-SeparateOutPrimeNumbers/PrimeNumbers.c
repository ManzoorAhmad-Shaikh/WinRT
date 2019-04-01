#include<stdio.h>

#define NUM 10

int main(void)
{
	int iArray[NUM];
	int i,num,j,count=0;
	
	printf("\n\n Enter the Array Elements : \n");
	for(i=0;i<NUM;i++)
	{
		scanf("\t %d",&num);
		if(num<0)
		{
		
			num= -1*num;
		}
		iArray[i]=num;
	}

	printf("\n\n Printing the Array Elements : \n");
	for(i=0;i<NUM;i++)
	{
		printf("\n\n\t %d",iArray[i]);	
	}

    printf("\n\n Prime Numbers Amongst the Array Elements Are : \n");
	for(i=0;i<NUM;i++)
	{
		for(j=1;j<=iArray[i];j++)
			{
				if((iArray[i]%j)==0)
					count++;			
			}
			if(count==2)
			printf("\n\n \t %d",iArray[i]);
			
			count=0;
	}

 return(0);
}
