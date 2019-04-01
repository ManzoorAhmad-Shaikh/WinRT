#include<stdio.h>
int main(void)
{
	int iArray[5][3]={{1,2,3},{2,4,6},{3,6,9},{4,8,12},{5,10,15}};
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
