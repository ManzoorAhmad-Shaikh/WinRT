#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	//var declaration
	char cArray1[LENGTH],cArray2[LENGTH],cArray_Concat[LENGTH];
	
	//code
	printf("\n\n Enter First String : ");
	gets(cArray1);
	printf("\n\n Enter First String : ");
	gets(cArray2);
	
		
	
	printf("\n\n Original String Entered by You Is : ");
	printf("\t %s",cArray1);
	//printf("\n\n Original String Entered by You Is : ");
	printf("\n \t %s",cArray2);
	
	strcpy(cArray1,cArray2);
	printf("\n\n \t Array1 = \t %s \n",cArray1);
	printf("\n\n \t Array2 = \t %s \n",cArray2);
	
	return(0);
}
