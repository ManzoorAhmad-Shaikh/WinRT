#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	void MyStrrev(char[],char[]);
	
	//var declaration
	char cArray[LENGTH],cArray_Reversed[LENGTH];
	
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
		
	MyStrrev(cArray_Reversed,cArray);	
	
	printf("\n\n Original String Entered by You Is : ");
	printf("\t %s",cArray);
	
	printf("\n\n \t Reversed String Is = \t %s \n",cArray_Reversed);
	
	return(0);
}

void MyStrrev(char str1[],char str2[])
{
	//function prototype
	int MyStrlen(char[]);

	//var declarations 
	int iStringLength = 0;
	int i, j, len;

	//code
	iStringLength = MyStrlen(str1);

	len = iStringLength - 1;

	for (i = 0, j = len; i < iStringLength, j >= 0; i++, j--)
	{
		str2[i] = str1[j];
	}
    //printf("\n \t %s",str2);
	//str2[i] = '\0';
}

int MyStrlen(char str[])
{
	//var declarations
	int j;
	int strlen = 0;

	for (j = 0; j < LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			strlen++;
	}
	return(strlen);
}

