#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	char strArray[5][10];
	int csize,strArray_size,strArray_elements,strArray_rows,strArray_columns;
 	int i;
	 	
	csize=sizeof(char);
	strArray_size=sizeof(strArray);
	
	printf("\n\n Size of Two Dimensional (2D) Char Array Is= %d\n",strArray_size);
	
	strArray_rows=strArray_size/sizeof(strArray[0]);
	printf("\n\n Number of Rows in 2D Char Array= %d\n",strArray_rows);
	
	strArray_columns=sizeof(strArray[0])/csize;
	printf("\n\n Number of Columns in 2D Char Array= %d\n",strArray_columns);
	
	strArray_elements=strArray_rows*strArray_columns;
	printf("\n\n Number of Elements in 2D Char Array= %d\n",strArray_elements);

	strcpy(strArray[0],"My");
	strcpy(strArray[1],"Name");
	strcpy(strArray[2],"Is");
	strcpy(strArray[3],"Manzoor");
	strcpy(strArray[4],"Shaikh");			
	
    printf("\n\n Strings in 2D Array : \n");

    for(i=0;i<strArray_rows;i++)
		{
		
    		printf("\n\n %s \n",strArray[i]);
				
		}
	printf("\n\n");
   

 return(0);
}
