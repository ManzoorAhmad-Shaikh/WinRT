#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{	
	int MyStrlen(char[]);
	
	//var declaration
	char cArray[LENGTH];
	int iStringLength=0;
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	printf("\n\n String Entered by You Is : ");
	printf("\t %s",cArray);
	
	iStringLength=MyStrlen(cArray);
	printf("\n\n \t Length Of String Is = %d Characters \n",iStringLength);
	
	return(0);
}

int MyStrlen(char str[])
{
	int j;
	int strlen=0;
	
	for(j=0;j<LENGTH;j++)
	{
		if(str[j]=='\0')
			break;
		else
			strlen++;
	}
	return(strlen);
}
