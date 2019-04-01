#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{	
	int MyStrlen(char[]);
	
	//var declaration
	char cArray[LENGTH],cArray_SpacesRemoved[LENGTH];
	int i,j,iStringLength=0;
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
		
	iStringLength=MyStrlen(cArray);
	j=0;
	for(i=0;i<iStringLength;i++)
	{
		if(cArray[i]==' ')
			continue;
		else
		{
			cArray_SpacesRemoved[j]=cArray[i];
			j++;
		}
	}
	
	cArray_SpacesRemoved[j] = '\0';
	
	printf("\n\n String Entered By You Is : %s",cArray);
	
	printf("\n\n String After Removal of  Spaces Is : %d\n",cArray_SpacesRemoved);
	
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
