#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	//var declaration
	char cArray[LENGTH];
	int iStringLength=0;
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	printf("\n\n String Entered by You Is : ");
	printf("\t %s",cArray);
	
	iStringLength=strlen(cArray);
	printf("\n\n \t Length Of String Is = %d Characters \n",iStringLength);
	
	return(0);
}
