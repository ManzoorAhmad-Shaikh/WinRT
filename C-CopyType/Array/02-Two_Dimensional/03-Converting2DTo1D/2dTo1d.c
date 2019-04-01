#include<stdio.h>

#define ROWS 5
#define COLUMNS 3

int main(void)
{
	int iArray2D[ROWS][COLUMNS];
	int iArray1D[ROWS*COLUMNS];
	
	int i,j,num;
	
	printf("\n\n Enter Elements of your choice to fill up 2D Array : ");
	for(i=0;i<ROWS;i++)
	{
		printf("For ROW %d : \n",(i+1));
		for(j=0;j<COLUMNS;j++)
		{
			printf("Enter Element Number %d : \n",(j+1));
			scanf("%d",&num);
			iArray2D[i][j]=num;
		}
		printf("\n\n");
	}
	
	printf("\n\n Two-Dimensional Int Array : ");
	for(i=0;i<ROWS;i++)
    {
	
    printf("\n ***** ROW %d ***** \n",(i+1));
    for(j=0;j<COLUMNS;j++)
    	{
	
    		printf("\n\n Array2D[%d][%d] = %d \n",i,j,iArray2D[i][j]);
				
		}
		printf("\n\n");
	}
	
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLUMNS;j++)
		{
			iArray1D[(i*COLUMNS)+j]=iArray2D[i][j];
		}
	}
	
	printf("\n\n One-Dimensional Array Of Integers : \n\n");
	for (i = 0; i < (ROWS * COLUMNS); i++)
	{
		printf("iArray1D[%d]  = %d\n", i, iArray1D[i]);
	}

	printf("\n\n");

	return(0);
}
