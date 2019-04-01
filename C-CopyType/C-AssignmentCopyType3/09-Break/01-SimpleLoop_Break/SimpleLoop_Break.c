#include <stdio.h>
#include <conio.h>
int main(void)
{
	//Variable declaration
	int i;
	char ch;

	//code
	printf("\n\n");

	printf("Manzoor :Printing Even Numbers From 1 to 100 For Every User Input. Exitting the Loop When User Enters Character 'Q' or 'q' : \n\n");
	printf("Manzoor : Enter Character 'Q' or 'q' To Exit Loop : \n\n");

	for (i = 1; i <= 100; i++)
	{
		printf("\tManzoor : %d\n", i);
		ch = getch();
		if (ch == 'Q' || ch == 'q')
		{
			break;
		}
	}

	printf("\n\n");
	printf("EXITTING LOOP.");
	printf("\n\n");

	return(0);
}
