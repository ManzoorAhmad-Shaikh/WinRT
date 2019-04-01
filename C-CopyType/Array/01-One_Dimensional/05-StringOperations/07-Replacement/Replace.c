#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{	
	int MyStrlen(char[]);
	
	//var declaration
	char cArray[LENGTH],cArray_VowelReplaced[LENGTH];
	int i,iStringLength=0;
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	strcpy(cArray_VowelReplaced,cArray);	
	iStringLength=MyStrlen(cArray_VowelReplaced);
	
	for(i=0;i<iStringLength;i++)
	{
		switch(cArray_VowelReplaced[i])
		{
			case 'A':
			case 'a':
			case 'E':
			case 'e':
			case 'I':
			case 'i':
			case 'O':
			case 'o':
			case 'U':
			case 'u':
					cArray_VowelReplaced[i]='*';
					break;		
		   
		    default:
		    		break;
		
		}
	}
	printf("\n\n String Entered By You Is : %s",cArray);
	
	printf("\n\n String After Replacement of Vovwels By * Is : \n");
	printf("\t %s",cArray_VowelReplaced);
	
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
