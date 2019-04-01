#include<stdio.h>

#define ROWS 5
#define COLUMNS 3
#define DEPTH 2

int main(void)
{
	int iArray[ROWS][COLUMNS][DEPTH]={ { { 9, 18 }, { 27, 36 }, { 45, 54 } },
										{ { 8, 16 }, { 24, 32 }, { 40, 48 } },
							            { { 7, 14 }, { 21, 28 }, { 35, 42 } },
							            { { 6, 12 }, { 18, 24 }, { 30, 36 } },
							            { { 5, 10 }, { 15, 20 }, { 25, 30 } } };
	
	
	int i,j,k;
	
	int iArray1D[ROWS*COLUMNS*DEPTH];
	

	printf("\n\n Displaying Three-Dimensional Int Array : ");
	for(i=0;i<ROWS;i++)
    {
	
    printf("\n ***** ROW %d ***** \n",(i+1));
    for(j=0;j<COLUMNS;j++)
    	{
			printf("\n ***** COLUMN %d ***** \n",(j+1));
			for(k=0;k<DEPTH;k++)
			{
					printf("\n\n Array[%d][%d][%d] = %d \n",i,j,k,iArray[i][j][k]);
			}
		printf("\n");		
		}
		printf("\n");
	}
	
	//Converting 3D To 2D
	for(i=0;i<ROWS;i++)
	{
		for(j=0;j<COLUMNS;j++)
		{
			for(k=0;k<DEPTH;k++)
			{
					iArray1D[(i*COLUMNS*DEPTH)+(j*DEPTH)+k]=iArray[i][j][k];
			}
		}
	}
	
	//Display
	printf("\n\n One-Dimensional Array Of Integers : \n\n");
	for (i = 0; i < (ROWS*COLUMNS*DEPTH); i++)
	{
		
				printf("iArray1D[%d]  = %d\n", i, iArray1D[i]);
		
	}

	return(0);
}
