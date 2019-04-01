#include<stdio.h>
#include<string.h>

#define LENGTH 512

#define SPACE ' '
#define FULLSTOP '.'
#define COMMA ','
#define EXCLAMATION '!'
#define QUESTION_MARK '?'

int main(void)
{	
	int MyStrlen(char[]);
	char MyToUpper(char);
		
	//var declaration
	char cArray[LENGTH],cArrayCapital[LENGTH];
	int iStringLength=0;
	int i,j;
		
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	iStringLength=MyStrlen(cArray);
	j=0;
	for(i=0;i<iStringLength;i++)
	{
		if(i==0)
		{
		cArrayCapital[j]=MyToUpper(cArray[i]);
		}
		
		else if(cArray[i]==SPACE)
		{
		 		cArrayCapital[j]=cArray[i];	
		 		cArrayCapital[j+1]=MyToUpper(cArray[i+1]);
		 		
		 		j++;
		 		i++;
		}
		else if((cArray[i]==FULLSTOP) || (cArray[i]==COMMA) || (cArray[i]==EXCLAMATION) || (cArray[i]==QUESTION_MARK) && (cArray[i]==SPACE))
		{
				cArrayCapital[j]=cArray[i];
				cArrayCapital[j+1]=SPACE;
				cArrayCapital[j+2]=MyToUpper(cArray[i+1]);
				j=j+2;
				i++;
		}
		else
		{
			cArrayCapital[j]=cArray[i];
		}
		
		j++;
	}
	
	cArrayCapital[j]='\0';
	
	printf("\n\n String Entered by You Is : ");
	printf("\t %s",cArray);
	
	
	printf("\n\n \t String After Capitalizing First Letter = %s \n",cArrayCapital);
	
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
char MyToUpper(char ch)
{
	int num;
	int c;
	
	num= 'a' - 'A';
	
	if((int)ch >= 97 && (int)ch>=122)
	{
		c=(int)ch-num;
		return((char)c);
	}
	else
		return(ch);
}

