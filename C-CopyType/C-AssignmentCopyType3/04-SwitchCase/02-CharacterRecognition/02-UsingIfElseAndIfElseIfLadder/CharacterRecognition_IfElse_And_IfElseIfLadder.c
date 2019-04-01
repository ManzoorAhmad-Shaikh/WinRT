#include <stdio.h> 
#include <conio.h> 

// ASCII Values For 'A' to 'Z' => 65 to 90
#define CHAR_ALPHABET_UPPER_CASE_BEGINNING 65     
#define CHAR_ALPHABET_UPPER_CASE_ENDING 90

// ASCII Values For 'a' to 'z' => 97 to 122
#define CHAR_ALPHABET_LOWER_CASE_BEGINNING 97		 
#define CHAR_ALPHABET_LOWER_CASE_ENDING 122		 

// ASCII Values For '0' to '9' => 48 to 57
#define CHAR_DIGIT_BEGINNING 48		 
#define CHAR_DIGIT_ENDING 57		 

int main(void)
{
	//variable declarations
	char ch;
	int chValue;

	//code
	printf("\n\n");

	printf("Manzoor : Enter Character : ");
	ch = getch();

	printf("\n\n");

	if ((ch == 'A' || ch == 'a') || (ch == 'E' || ch == 'e') || (ch == 'I' || ch == 'i') || (ch == 'O' || ch == 'o') || (ch == 'U' || ch == 'u'))
	{
		printf("Manzoor :Character \'%c\' Entered By You, Is A VOWEL CHARACTER From The English Alphabet !!!\n\n", ch);
	}

	else
	{
		chValue = (int)ch;

		//If The Character Has ASCII Value Between 65 AND 90 OR Between 97 AND 122, It Is Still A Letter Of The Alphabet, But It Is A 'CONSONANT', and NOT a 'VOWEL'...
		if ((chValue >= CHAR_ALPHABET_UPPER_CASE_BEGINNING && chValue <= CHAR_ALPHABET_UPPER_CASE_ENDING) || (chValue >= CHAR_ALPHABET_LOWER_CASE_BEGINNING && chValue <= CHAR_ALPHABET_LOWER_CASE_ENDING))
		{
			printf("Manzoor : Character \'%c\' Entered By You, Is A CONSONANT CHARACTER From The English Alphabet !!!\n\n", ch);
		}

		else if (chValue >= CHAR_DIGIT_BEGINNING && chValue <= CHAR_DIGIT_ENDING)
		{
			printf("Manzoor : Character \'%c\' Entered By You, Is A DIGIT CHARACTER !!!\n\n", ch);
		}

		else
		{
			printf("Manzoor :Character \'%c\' Entered By You, Is A SPECIAL CHARACTER !!!\n\n", ch);
		}
	}

	return(0);
}
