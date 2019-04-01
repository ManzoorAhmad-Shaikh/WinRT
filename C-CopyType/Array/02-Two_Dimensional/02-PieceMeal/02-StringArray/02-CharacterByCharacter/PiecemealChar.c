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

// ****** ROW 1 / STRING 1 ******
	strArray[0][0] = 'M';
	strArray[0][1] = 'y';
	strArray[0][2] = '\0';

	// ****** ROW 2 / STRING 2 ******
	strArray[1][0] = 'N';
	strArray[1][1] = 'a';
	strArray[1][2] = 'm';
	strArray[1][3] = 'e';
	strArray[1][4] = '\0';

	// ****** ROW 3 / STRING 3 ******
	strArray[2][0] = 'I';
	strArray[2][1] = 's';
	strArray[2][2] = '\0'; //NULL-TERMINATING CHARACTER

	// ****** ROW 4 / STRING 4 ******
	strArray[3][0] = 'M';
	strArray[3][1] = 'a';
	strArray[3][2] = 'n';
	strArray[3][3] = 'z';
	strArray[3][4] = 'o';
	strArray[3][5] = 'o';
	strArray[3][6] = 'r';
	strArray[3][7] = '\0';

	// ****** ROW 5 / STRING 5 ******
	strArray[4][0] = 'S';
	strArray[4][1] = 'h';
	strArray[4][2] = 'a';
	strArray[4][3] = 'i';
	strArray[4][4] = 'k';
	strArray[4][5] = 'h';
	strArray[4][6] = '\0';			
	
    printf("\n\n Strings in 2D Array : \n");

    for(i=0;i<strArray_rows;i++)
		{
		
    		printf("\n\n %s \n",strArray[i]);
				
		}
	printf("\n\n");
   

 return(0);
}
