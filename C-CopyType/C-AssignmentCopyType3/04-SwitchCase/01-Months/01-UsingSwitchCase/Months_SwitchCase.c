#include <stdio.h>
int main(void)
{
	//Variable declarations
	int numMonth;

	//code
	printf("\n\n");

	printf("Manzoor : Enter Number Of Month (1 to 12) : ");
	scanf("%d", &numMonth);

	printf("\n\n");

	switch (numMonth)
	{
	case 1: //like 'if'
		printf("Manzoor : Month Number %d Is JANUARY !!!\n\n", numMonth);
		break;

	case 2: //like 'else if'
		printf("Manzoor :Month Number %d Is FEBRUARY !!!\n\n", numMonth);
		break;

	case 3: //like 'else if'
		printf("Manzoor : Month Number %d Is MARCH !!!\n\n", numMonth);
		break;

	case 4: //like 'else if'
		printf("Manzoor : Month Number %d Is APRIL !!!\n\n", numMonth);
		break;

	case 5: //like 'else if'
		printf("Manzoor :Month Number %d Is MAY !!!\n\n", numMonth);
		break;

	case 6: //like 'else if'
		printf("Manzoor : Month Number %d Is JUNE !!!\n\n", numMonth);
		break;

	case 7: //like 'else if'
		printf("Manzoor : Month Number %d Is JULY !!!\n\n", numMonth);
		break;

	case 8: //like 'else if'
		printf("Manzoor : Month Number %d Is AUGUST !!!\n\n", numMonth);
		break;

	case 9: //like 'else if'
		printf("Manzoor : Month Number %d Is SEPTEMBER !!!\n\n", numMonth);
		break;

	case 10: //like 'else if'
		printf("Manzoor :Month Number %d Is OCTOBER !!!\n\n", numMonth);
		break;

	case 11: //like 'else if'
		printf("Manzoor : Month Number %d Is NOVEMBER !!!\n\n", numMonth);
		break;

	case 12: //like 'else if'
		printf("Month Number %d Is DECEMBER !!!\n\n", numMonth);
		break;

	default: //like ending OPTIONAL 'else'...
		printf("Manzoor : Invalid Month Number %d Entered !!! Please Try Again...\n\n", numMonth);
		break;
	}

	printf("Manzoor :Switch Case Block Complete !!!\n");

	return(0);
}
