#include <stdio.h>
int main(void)
{
	//variable declarations
	int numMonth;

	//code
	printf("\n\n");

	printf("Manzoor : Enter Number Of Month (1 to 12) : ");
	scanf("%d", &numMonth);

	printf("\n\n");

	// IF - ELSE - IF LADDER BEGINS FROM HERE...
	if (numMonth == 1) //like 'case 1'
		printf("Manzoor :Month Number %d Is JANUARY !!!\n\n", numMonth);

	else if (numMonth == 2) //like 'case 2'
		printf("Manzoor : Month Number %d Is FEBRUARY !!!\n\n", numMonth);

	else if (numMonth == 3) //like 'case 3'
		printf("Manzoor : Month Number %d Is MARCH !!!\n\n", numMonth);

	else if (numMonth == 4) //like 'case 4'
		printf("Manzoor : Month Number %d Is APRIL !!!\n\n", numMonth);

	else if (numMonth == 5) //like 'case 5'
		printf("Manzoor : Month Number %d Is MAY !!!\n\n", numMonth);

	else if (numMonth == 6) //like 'case 6'
		printf("Manzoor :Month Number %d Is JUNE !!!\n\n", numMonth);

	else if (numMonth == 7) //like 'case 7'
		printf("Manzoor : Month Number %d Is JULY !!!\n\n", numMonth);

	else if (numMonth == 8) //like 'case 8'
		printf("Manzoor : Month Number %d Is AUGUST !!!\n\n", numMonth);

	else if (numMonth == 9) //like 'case 9'
		printf("Manzoor : Month Number %d Is SEPTEMBER !!!\n\n", numMonth);

	else if (numMonth == 10) //like 'case 10'
		printf("Manzoor :Month Number %d Is OCTOBER !!!\n\n", numMonth);

	else if (numMonth == 11) //like 'case 11'
		printf("Manzoor :Month Number %d Is NOVEMBER !!!\n\n", numMonth);

	else if (numMonth == 12) //like 'case 12'
		printf("Manzoor : Month Number %d Is DECEMBER !!!\n\n", numMonth);

	else //like 'default'.Just like 'default' is optional in switch-case, so is 'else' in the if-else if-else ladder.
		printf("Manzoor :Invalid Month Number %d Entered !!! Please Try Again...\n\n", numMonth);

	printf("Manzoor :If - Else If - Else Ladder Complete !!!\n");

	return(0);
}
