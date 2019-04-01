#include<stdio.h>
int main(void)
{
	int iArray[5][3]={{1,2,3},{2,4,6},{3,6,9},{4,8,12},{5,10,15}};
	int isize,iArray_size,iArray_elements,iArray_rows,iArray_columns;
	
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

    printf("\n ***** ROW 1 ***** \n");
    printf("\n iArray[0][0] = %d \n",iArray[0][0]);
	printf("\n iArray[0][1] = %d \n",iArray[0][1]);
	printf("\n iArray[0][2] = %d \n",iArray[0][2]);	
    
    printf("\n\n ***** ROW 2 ***** \n");
    printf("\n iArray[1][0] = %d \n",iArray[1][0]);
	printf("\n iArray[1][1] = %d \n",iArray[1][1]);
	printf("\n iArray[1][2] = %d \n",iArray[1][2]);	
 
 	printf("\n\n ***** ROW 3 ***** \n");
    printf("\n iArray[2][0] = %d \n",iArray[2][0]);
	printf("\n iArray[2][1] = %d \n",iArray[2][1]);
	printf("\n iArray[2][2] = %d \n",iArray[2][2]);	
       
    printf("\n\n ***** ROW 4 ***** \n");
    printf("\n iArray[3][0] = %d \n",iArray[3][0]);
	printf("\n iArray[3][1] = %d \n",iArray[3][1]);
	printf("\n iArray[3][2] = %d \n",iArray[3][2]);	
    
	printf("\n\n ***** ROW 5 ***** \n");
    printf("\n iArray[4][0] = %d \n",iArray[4][0]);
	printf("\n iArray[4][1] = %d \n",iArray[4][1]);
	printf("\n iArray[4][2] = %d \n",iArray[4][2]);	
    

 return(0);
}
