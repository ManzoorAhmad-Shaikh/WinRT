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
	int i,j,k;
	
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

	for(i=0;i<iArray_width;i++)
	{
		printf("\n ***** ROW %d ***** \n",(i+1));
		for(j=0;j<iArray_height;j++)
		{
			printf(" ***** COLUMN %d ***** \n",(j+1));
    	
    		for(k=0;k<iArray_depth;k++)
    		{
				printf("\n iArray[0][0][0] = %d \n",i,j,k,iArray[i][j][k]);
			}
			printf("\n");
		}
		printf("\n\n");
	}

 return(0);
}
