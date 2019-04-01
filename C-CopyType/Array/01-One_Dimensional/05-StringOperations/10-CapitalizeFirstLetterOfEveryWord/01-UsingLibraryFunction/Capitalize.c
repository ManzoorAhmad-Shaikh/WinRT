#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{	
	int MyStrlen(char[]);
	
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
		cArrayCapital[j]=toupper(cArray[i]);
		}
		
		else if(cArray[i]==' ')
		{
		 		cArrayCapital[j]=cArray[i];	
		 		cArrayCapital[j+1]=toupper(cArray[i+1]);
		 		
		 		j++;
		 		i++;
		}
		else
		{
				cArrayCapital[j]=cArray[i];
		}
		j++;
	}
	
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
