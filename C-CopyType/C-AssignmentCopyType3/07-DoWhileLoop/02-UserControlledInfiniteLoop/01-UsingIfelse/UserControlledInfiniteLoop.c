#include <stdio.h>
int main(void)
{
	//Variable declarations
	char option, ch = '\0';

	//Code
	printf("\n\n");
	printf("Manzoor: Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop : \n\n\n");
	printf("Manzoor : Enter 'Y' oy 'y' To Initiate User Controlled Infinite Loop : ");
	printf("\n\n");
	option = getch();
	if (option == 'Y' || option == 'y')
	{
		do
		{
			printf("Manzoor: In Loop...\n");
			ch = getch(); //Control flow waits for character input...
			if (ch == 'Q' || ch == 'q')
				break; //user controlled Exitting From Infinite Loop
		} while (1); //infinite Loop

		printf("\n\n");
		printf("Manzoor:  Exiting User Controlled Infinite Loop.");
		printf("\n\n");
	}

	else
		printf("You Must Press 'Y' or 'y' To Initiate The User Controlled Infinite Loop....Please Try Again...\n\n");

	return(0);
}
