#include <stdio.h>

#define LENGTH 512

int main(void)
{
	
	int MyStrlen(char[]);
	//void MyStrcpy(char[], char[]);

	//variable declarations 
	char cArray[LENGTH], cArray_SpacesRemoved[LENGTH]; 
	int iStringLength;
	int i, j;

	//code

	printf("\n\n");
	printf("Enter A String : \n\n");
	gets(cArray);

	iStringLength = MyStrlen(cArray);
	j = 0;
	for (i = 0; i < iStringLength; i++)
	{
		if (cArray[i] == ' ')
			continue;
		else
		{
			cArray_SpacesRemoved[j] = cArray[i];
			j++;
		}
	}

	cArray_SpacesRemoved[j] = '\0';

	// *** STRING OUTPUT ***
	printf("\n\n");
	printf("String Entered By You Is : \n\n");
	printf("%s\n", cArray);

	printf("\n\n");
	printf("String After Removal Of Spaces Is : \n\n");
	printf("%s\n", cArray_SpacesRemoved);

	return(0);
}

int MyStrlen(char str[])
{
	//variable declarations
	int j;
	int string_length = 0;

	//code
	// *** DETERMINING EXACT LENGTH OF THE STRING, BY DETECTING THE FIRST OCCURENCE OF NULL-TERMINATING CHARACTER ( \0 ) ***
	for (j = 0; j < LENGTH; j++)
	{
		if (str[j] == '\0')
			break;
		else
			string_length++;
	}
	return(string_length);
}

