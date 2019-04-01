#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{	
	int MyStrlen(char[]);
	
	//var declaration
	char cArray[LENGTH];
	int i,iStringLength=0;
	int word_count=0,space_count=0;
	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
		
	iStringLength=MyStrlen(cArray);
	
	for(i=0;i<iStringLength;i++)
	{
		switch(cArray[i])
		{
			case 32:
					space_count++;
					break;		
		   
		    default:
		    		break;
		
		}
	}
	
	word_count=space_count+1;
	
	printf("\n\n String Entered By You Is : %s",cArray);
	
	printf("\n\n Number of Spaces In the String Is : %d\n",space_count);
	printf("\n\n Number of Words In the String Is : %d\n",word_count);
	
	
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
