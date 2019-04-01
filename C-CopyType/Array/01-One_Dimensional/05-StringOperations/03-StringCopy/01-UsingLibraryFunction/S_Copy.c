#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	//var declaration
	char cArray[LENGTH],cArray_Copy[LENGTH];
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	strcpy(cArray_Copy,cArray);	
	
	printf("\n\n Original String Entered by You Is : ");
	printf("\t %s",cArray);
	
	printf("\n\n \t Copied String (i.e. 'cArray_Copy[]') Is = \t %s \n",cArray_Copy);
	
	return(0);
}
