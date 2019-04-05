#include<stdio.h>
#include<ctype.h>
#include<string.h>

#define LENGTH 1024

struct CharacterCount
{
	char ch;
	int chcount;
}character_and_count[]={{'A',0},{'B',0},{'C',0},{'D',0},{'E',0},{'F',0},{'G',0},
						{'H',0},{'I',0},{'J',0},{'K',0},{'L',0},{'M',0},
						{'N',0},{'O',0},{'P',0},{'Q',0},{'R',0},{'S',0},
						{'T',0},{'U',0},{'V',0},{'W',0},{'X',0},{'Y',0},{'Z',0}};
	
#define SIZE_OF_ENTIRE_ARRAY_OF_STRUCTS sizeof(character_and_count)
#define SIZE_OF_ONE_STRUCT_FROM_ARRAY_OF_STRUCTS sizeof(character_and_count[0])
#define NUM_ELEMENTS_IN_ARRAY (SIZE_OF_ENTIRE_ARRAY_OF_STRUCTS / SIZE_OF_ONE_STRUCT_FROM_ARRAY_OF_STRUCTS)

						
int main(void)
{
	char str[LENGTH];
	int i,j,actual_slength;
	
	printf("\n\n Enter a String : \n");
	gets(str);
	
	actual_slength=strlen(str);
	
	printf("\n\n The String you have Entered is : ");
	printf(" %s \n",str);
	
	for(i=0;i<actual_slength;i++)
	{
		for(j=0;j<NUM_ELEMENTS_IN_ARRAY;j++)
		{
			str[i]=toupper(str[i]);
			
			if(str[i]==character_and_count[j].ch)
			character_and_count[j].chcount++;
		}
	}
	
	printf("\n\n The Number of Occurences of all characters from the Alphabets are as Follows : ");
	for(i=0;i<NUM_ELEMENTS_IN_ARRAY;i++)
	{
		printf("\n Character %c = %d\n",character_and_count[i].ch,character_and_count[i].chcount);
	}
	
	printf("\n\n ");
	
	return(0);
}						
