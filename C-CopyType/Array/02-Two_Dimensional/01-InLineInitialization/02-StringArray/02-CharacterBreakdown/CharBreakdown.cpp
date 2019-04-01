#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	char strArray[10][15]={"Hello!", "Welcome", "To", "Real", "Time", "Rendering", "Batch", "(2018-19-20)", "Of", "ASTROMEDICOMP."};
	
	int iStrLengths[10],strArray_size,strArray_rows;
	int i,j;
	
	strArray_size=sizeof(strArray);
	
	//printf("\n\n Size of Two Dimensional (2D) Character Array Is= %d\n",strArray_size);
	
	strArray_rows=strArray_size/sizeof(strArray[0]);
	//printf("\n\n Number of Rows in 2D Char Array= %d\n",strArray_rows);
	
	
	for(i=0;i<strArray_rows;i++)
	{
		iStrLengths[i]=strlen(strArray[i]);	
	}
	
	printf("\n\n The Entire String Array : \n\n");
	for(i=0;i<strArray_rows;i++)
	{
		printf("%s ",strArray[i]);
	}
	
		
    printf("\n\n Strings in 2D Array : \n");
    
	for(i=0;i<strArray_rows;i++)
	{
		printf(" String Number %d => %s \n\n",(i+1),strArray[i]);
		for(j=0;j<iStrLengths[i];j++)
		{
			printf("Character %d = %c\n",(j+1),strArray[i][j]);
		}
		printf("\n\n");
	}
    

 return(0);
}
