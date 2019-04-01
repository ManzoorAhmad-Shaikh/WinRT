#include<stdio.h>
#include<string.h>

int main(void)
{
	char strArray[10][15]={"Hello!", "Welcome", "To", "Real", "Time", "Rendering", "Batch", "(2018-19-20)", "Of", "ASTROMEDICOMP."};
	
	int char_size,strArray_size,strArray_elements,strArray_rows,strArray_columns;
	int strActual_chars=0;
	int i;
	
	char_size=sizeof(char);
	strArray_size=sizeof(strArray);
	
	printf("\n\n Size of Two Dimensional (2D) Character Array Is= %d\n",strArray_size);
	
	strArray_rows=strArray_size/sizeof(strArray[0]);
	printf("\n\n Number of Rows in 2D Char Array= %d\n",strArray_rows);
	
	strArray_columns=sizeof(strArray[0])/char_size;
	printf("\n\n Number of Columns in 2D Char Array= %d\n",strArray_columns);
	
	strArray_elements=strArray_rows*strArray_columns;
	printf("\n\n Number of Elements in 2D Char Array= %d\n",strArray_elements);
	
	for(i=0;i<strArray_rows;i++)
	{
		strActual_chars=strActual_chars + strlen(strArray[i]);	
	}
	printf("\n\n Actual Number of Elements in 2D Char Array= %d\n",strActual_chars);
	
		
    printf("\n\n Strings in 2D Array : \n");

    
    printf(" %s ",strArray[0]);
    printf(" %s ",strArray[1]);
    printf(" %s ",strArray[2]);
    printf(" %s ",strArray[3]);
    printf(" %s ",strArray[4]);
    printf(" %s ",strArray[5]);
    printf(" %s ",strArray[6]);
    printf(" %s ",strArray[7]);
    printf(" %s ",strArray[8]);
    printf(" %s \n\n",strArray[9]);

 return(0);
}
