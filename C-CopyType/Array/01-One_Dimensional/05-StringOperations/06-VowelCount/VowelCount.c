#include<stdio.h>
#include<string.h>

#define LENGTH 512

int main(void)
{	
	int MyStrlen(char[]);
	
	//var declaration
	char cArray[LENGTH];
	int i,iStringLength=0;
	int count_A=0,count_E=0,count_I=0,count_O=0,count_U=0;	
	//code
	printf("\n\n Enter a String : ");
	gets(cArray);
	
	printf("\n\n String Entered by You Is : ");
	printf("\t %s",cArray);
	
	iStringLength=MyStrlen(cArray);
	
	for(i=0;i<iStringLength;i++)
	{
		switch(cArray[i])
		{
			case 'A':
			case 'a':
					count_A++;
					break;
			
			case 'E':
			case 'e':
					count_E++;
					break;		
				
			case 'I':
			case 'i':
					count_I++;
					break;		
			
			case 'O':
			case 'o':
					count_O++;
					break;
					
			case 'U':
			case 'u':
					count_U++;
					break;		
		   
		    default:
		    		break;
		
		}
	}
	
	printf("\n\n In The String The Vowels And Number Of thier Occurances Are as follows : \n");
	printf("\n 'A' Has Occured = %d Times ... ",count_A);
	printf("\n 'E' Has Occured = %d Times ... ",count_E);
	printf("\n 'I' Has Occured = %d Times ... ",count_I);
	printf("\n 'O' Has Occured = %d Times ... ",count_O);
	printf("\n 'U' Has Occured = %d Times ... ",count_U);
	
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
