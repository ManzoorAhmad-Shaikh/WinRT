#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	void MyStrcat(char[],char[]);
	
	//var declaration
	char cArray_One[LENGTH],cArray_Two[LENGTH];
	
	
	//code
	printf("\n\n Enter First String : ");
	gets(cArray_One);
	
	printf("\n\n Enter Second String : ");
	gets(cArray_Two);
			
	
	printf("\n\n Original First String Entered by You Is : ");
	printf("\t %s",cArray_One);
   
   	printf("\n\n Original Second String Entered by You Is : ");
	printf("\t %s",cArray_Two);
	
	MyStrcat(cArray_One,cArray_Two);
		
	printf("\n\n \t cArray_One Is = \t %s \n",cArray_One);
	printf("\n\n \t cArray_Two Is = \t %s \n",cArray_Two);	
	
	return(0);
}

void MyStrcat(char str1[],char str2[])
{
	//function prototype
	int MyStrlen(char[]);

	//var declarations 
	int iStringLength_str1 = 0,iStringLength_str2 = 0;
	int i, j;

	//code
	iStringLength_str1 = MyStrlen(str1);
	iStringLength_str2 = MyStrlen(str2);	

	for (i = iStringLength_str2,j=0; j < iStringLength_str1; i++, j++)
	{
		str2[i] = str1[j];
	}
    //printf("\n \t %s",str2);
	str2[i] = '\0';
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

