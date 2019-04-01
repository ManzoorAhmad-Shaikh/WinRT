#	include<stdio.h>
int main(void)
{
	int iArray[5][3][2]={ { { 9, 18 }, { 27, 36 }, { 45, 54 } },
							{ { 8, 16 }, { 24, 32 }, { 40, 48 } },
							{ { 7, 14 }, { 21, 28 }, { 35, 42 } },
							{ { 6, 12 }, { 18, 24 }, { 30, 36 } },
							{ { 5, 10 }, { 15, 20 }, { 25, 30 } } };
							
	int isize,iArray_size,iArray_elements,iArray_width,iArray_height,iArray_depth;
	
	isize=sizeof(int);
	iArray_size=sizeof(iArray);
	
	printf("\n\n Size of Two Dimensional (2D) Integer Array Is= %d\n",iArray_size);
	
	iArray_width=iArray_size/sizeof(iArray[0]);
	printf("\n\n Number of Rows(Width) in 3D Int Array= %d\n",iArray_width);
	
	iArray_height=sizeof(iArray[0])/isize;
	printf("\n\n Number of Columns(Height) in 3D Int Array= %d\n",iArray_height);
	
	iArray_depth=sizeof(iArray[0][0])/isize;
	printf("\n\n Depth in 3D Int Array= %d\n",iArray_depth);
	
	iArray_elements=iArray_width*iArray_height*iArray_depth;
	printf("\n\n Number of Elements in 3D Int Array= %d\n",iArray_elements);
	
    printf("\n\n Elements in 3D Array : \n");

    printf("\n ***** ROW 1 ***** \n");
        printf(" ***** COLUMN 1 ***** \n");
    printf("\n iArray[0][0][0] = %d \n",iArray[0][0][0]);
	printf("\n iArray[0][0][1] = %d \n",iArray[0][0][1]);
    printf("\n");
    
    printf(" ***** COLUMN 2 ***** \n");
	printf("\n iArray[0][1][0] = %d \n",iArray[0][1][0]);
	printf("\n iArray[0][1][1] = %d \n",iArray[0][1][1]);
    printf("\n");
    
 	printf(" ***** COLUMN 3 ***** \n");
	printf("\n iArray[0][2][0] = %d \n",iArray[0][2][0]);
	printf("\n iArray[0][2][2] = %d \n",iArray[0][2][1]);
    printf("\n\n");
       
    printf("\n ***** ROW 2 ***** \n");
    printf(" ***** Column 1 ***** \n");
    printf("\n iArray[1][0][0] = %d \n",iArray[1][0][0]);
	printf("\n iArray[1][0][1] = %d \n",iArray[1][0][1]);
    
printf("****** COLUMN 2 ******\n");
	printf("\n iArray[1][1][0] = %d\n", iArray[1][1][0]);
	printf("\n iArray[1][1][1] = %d\n", iArray[1][1][1]);
	printf("\n");

	printf("****** COLUMN 3 ******\n");
	printf("\n iArray[1][2][0] = %d\n", iArray[1][2][0]);
	printf("\n iArray[1][2][1] = %d\n", iArray[1][2][1]);
	printf("\n\n");

	// ****** ROW 3 ******
	printf("****** ROW 3 ******\n");
	printf("****** COLUMN 1 ******\n");
	printf("\n iArray[2][0][0] = %d\n", iArray[2][0][0]);
	printf("\n iArray[2][0][1] = %d\n", iArray[2][0][1]);
	printf("\n");

	printf("****** COLUMN 2 ******\n");
	printf("\n iArray[2][1][0] = %d\n", iArray[2][1][0]);
	printf("\n iArray[2][1][1] = %d\n", iArray[2][1][1]);
	printf("\n");

	printf("****** COLUMN 3 ******\n");
	printf("\n iArray[2][2][0] = %d\n", iArray[2][2][0]);
	printf("\n iArray[2][2][1] = %d\n", iArray[2][2][1]);
	printf("\n\n");

	// ****** ROW 4 ******
	printf("****** ROW 4 ******\n");
	printf("****** COLUMN 1 ******\n");
	printf("\n iArray[3][0][0] = %d\n", iArray[3][0][0]);
	printf("\n iArray[3][0][1] = %d\n", iArray[3][0][1]);
	printf("\n");

	printf("****** COLUMN 2 ******\n");
	printf("\n iArray[3][1][0] = %d\n", iArray[3][1][0]);
	printf("\n iArray[3][1][1] = %d\n", iArray[3][1][1]);
	printf("\n");

	printf("****** COLUMN 3 ******\n");
	printf("\n iArray[3][2][0] = %d\n", iArray[3][2][0]);
	printf("\n iArray[3][2][1] = %d\n", iArray[3][2][1]);
	printf("\n\n");

	// ****** ROW 5 ******
	printf("****** ROW 5 ******\n");
	printf("****** COLUMN 1 ******\n");
	printf("\n iArray[4][0][0] = %d\n", iArray[4][0][0]);
	printf("\n iArray[4][0][1] = %d\n", iArray[4][0][1]);
	printf("\n");

	printf("****** COLUMN 2 ******\n");
	printf("\n iArray[4][1][0] = %d\n", iArray[4][1][0]);
	printf("\n iArray[4][1][1] = %d\n", iArray[4][1][1]);
	printf("\n");

	printf("****** COLUMN 3 ******\n");
	printf("\n iArray[4][2][0] = %d\n", iArray[4][2][0]);
	printf("\n iArray[4][2][1] = %d\n", iArray[4][2][1]);
	printf("\n\n");
	
    

 return(0);
}
