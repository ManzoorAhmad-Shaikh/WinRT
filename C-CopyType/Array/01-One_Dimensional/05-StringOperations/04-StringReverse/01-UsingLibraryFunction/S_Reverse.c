#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	//var declaration
	char cArray[LENGTH];
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
		
	
	printf("\n\n Original String Entered by You Is : ");
	printf("\t %s",cArray);
	
	printf("\n\n \t Reversed String Is = \t %s \n",strrev(cArray));
	
	return(0);
}
