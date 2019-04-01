#include <stdio.h>
int main(void)
{
	//Variable declarations
	char option, ch = '\0';

	//code
	printf("\n\n");
	printf("Manzoor:Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop : \n\n");

	do
	{
		do
		{
			printf("\n");
			printf("Manzoor: In Loop...\n");
			ch = getch(); //Control flow waits for character input...
		} while (ch != 'Q' && ch != 'q');
		printf("\n\n");
		printf("Manzoor: EXITTING USER CONTROLLED INFINITE LOOP...");

		printf("\n\n");
		printf("Manzoor: DO YOU WANT TO BEGIN USER CONTROLLED INFINITE LOOP AGAIN?..(Y/y - Yes, Any Other Key - No) : ");
		option = getch();
	}while (option == 'Y' || option == 'y');

	return(0);
}
