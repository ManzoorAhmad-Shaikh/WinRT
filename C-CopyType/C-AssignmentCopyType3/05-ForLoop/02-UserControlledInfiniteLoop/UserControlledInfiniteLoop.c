#include <stdio.h>
int main(void)
{
	//variable declarations
	char option, ch = '\0';

	//code
	printf("\n\n");
	printf("Manzoor : Once The Infinite Loop Begins, Enter 'Q' or 'q' To Quit The Infinite For Loop : \n\n");
	printf("Manzoor : Enter 'Y' oy 'y' To Initiate User Controlled Infinite Loop : ");
	printf("\n\n");
	option = getch();
	if (option == 'Y' || option == 'y')
	{
		for (;;) //Infinite Loop
		{
			printf("Manzoor : In Loop...\n");
			ch = getch();
			if (ch == 'Q' || ch == 'q')
				break; //User Controlled Exitting From Infinite Loop
		}
	}

	printf("\n\n");
	printf("Manzoor : Exitting Uer Controlled INFINITE Loop.");
	printf("\n\n");

	return(0);
}
