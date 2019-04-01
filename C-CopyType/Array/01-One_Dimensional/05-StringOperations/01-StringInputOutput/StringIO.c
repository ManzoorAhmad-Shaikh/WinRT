#include<stdio.h>

#define MAX_STRING_LENGTH 512

int main(void)
{
	char cArray[MAX_STRING_LENGTH];
	
	//code
	printf("\n\n Enter a String : \n");
	gets(cArray);
	
	printf("\n\n String Entered by You : ");
	printf("\t %s",cArray);
	
	return(0);
}
