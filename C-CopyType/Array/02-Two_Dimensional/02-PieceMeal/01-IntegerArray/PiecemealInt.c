#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	int iArray[3][5];
	int isize,iArray_size,iArray_elements,iArray_rows,iArray_columns;
 	int i,j;
	 	
	isize=sizeof(int);
	iArray_size=sizeof(iArray);
	
	printf("\n\n Size of Two Dimensional (2D) Integer Array Is= %d\n",iArray_size);
	
	iArray_rows=iArray_size/sizeof(iArray[0]);
	printf("\n\n Number of Rows in 2D Int Array= %d\n",iArray_rows);
	
	iArray_columns=sizeof(iArray[0])/isize;
	printf("\n\n Number of Columns in 2D Int Array= %d\n",iArray_columns);
	
	iArray_elements=iArray_rows*iArray_columns;
	printf("\n\n Number of Elements in 2D Int Array= %d\n",iArray_elements);
	
    printf("\n\n Elements in 2D Array : \n");

// ****** ROW 1 ******
	iArray[0][0] = 21;
	iArray[0][1] = 42;
	iArray[0][2] = 63;
	iArray[0][3] = 84;
	iArray[0][4] = 105;

	// ****** ROW 2 ******
	iArray[1][0] = 22;
	iArray[1][1] = 44;
	iArray[1][2] = 66;
	iArray[1][3] = 88;
	iArray[1][4] = 110;

	// ****** ROW 3 ******
	iArray[2][0] = 23;
	iArray[2][1] = 46;
	iArray[2][2] = 69;
	iArray[2][3] = 92;
	iArray[2][4] = 115;

    for(i=0;i<iArray_rows;i++)
    {
	
    printf("\n ***** ROW %d ***** \n",(i+1));
    for(j=0;j<iArray_columns;j++)
    	{
	
    		printf("\n\n iArray[%d][%d] = %d \n",i,j,iArray[i][j]);
				
		}
	}
   

 return(0);
}
