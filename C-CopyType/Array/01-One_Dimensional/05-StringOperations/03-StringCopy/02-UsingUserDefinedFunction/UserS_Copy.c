#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{
	void MyStrcpy(char[],char[]);
	
	//var declaration
	char cArray[LENGTH],cArray_Copy[LENGTH];
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	MyStrcpy(cArray_Copy,cArray);	
	
	printf("\n\n Original String Entered by You Is : ");
	printf("\t %s",cArray);
	
	printf("\n\n \t Copied String (i.e. 'cArray_Copy[]') Is = \t %s \n",cArray_Copy);
	
	return(0);
}

void MyStrcpy(char str1[],char str2[])
{
	int MyStrlen(char[]);
	
	int j,istrlen=0;

    istrlen=MyStrlen(str1);	
	for(j=0;j<istrlen;j++)
	{
	
		str2[j]=str1[j];
			
	//str2[j]='\0';
	}
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
