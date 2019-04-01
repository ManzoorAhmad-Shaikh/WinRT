#include <stdio.h> 
#include <conio.h> 

int main(void)
{
	//variable declarations
	int a, b;
	int result;

	char option, optionDivision;

	//code
	printf("\n\n");

	printf("Manzoor :Enter Value For 'A' : ");
	scanf("%d", &a);

	printf("Manzoor : Enter Value For 'B' : ");
	scanf("%d", &b);

	printf("Manzoor : Enter Option In Character : \n\n");
	printf("Manzoor : 'A' or 'a' For Addition : \n");
	printf("Manzoor : 'S' or 's' For Subtraction : \n");
	printf("Manzoor :'M' or 'm' For Multiplication : \n");
	printf("Manzoor : 'D' or 'd' For Division : \n\n");

	printf("Manzoor : Enter Option : ");
	option = getch();

	printf("\n\n");

	switch (option)
	{
	// FALL THROUGH CONSITION FOR 'A' and 'a'
	case 'A':
	case 'a':
		result = a + b;
		printf("Manzoor :Addition Of A = %d And B = %d Gives Result %d !!!\n\n", a, b, result);
		break;

	// FALL THROUGH CONSITION FOR 'S' and 's'
	case 'S':
	case 's':
		if (a >= b)
		{
			result = a - b;
			printf("Manzoor :Subtraction Of B = %d From A = %d Gives Result %d !!!\n\n", b, a, result);
		}
		else
		{
			result = b - a;
			printf("Manzoor : Subtraction Of A = %d From B = %d Gives Result %d !!!\n\n", a, b, result);
		}
		break;

	// FALL THROUGH CONSITION FOR 'M' and 'm'
	case 'M':
	case 'm':
		result = a * b;
		printf("Manzoor : Multiplication Of A = %d And B = %d Gives Result %d !!!\n\n", a, b, result);
		break;

	// FALL THROUGH CONSITION FOR 'D' and 'd'
	case 'D':
	case 'd':
		printf("Manzoor : Enter Option In Character : \n\n");
		printf("Manzoor :'Q' or 'q' or '/' For Quotient Upon Division : \n");
		printf("Manzoor : 'R' or 'r' or '%%' For Remainder Upon Division : \n");

		printf("Manzoor : Enter Option : ");
		optionDivision = getch();

		printf("\n\n");

		switch (optionDivision)
		{
		// FALL THROUGH CONSITION FOR 'Q' and 'q' and '/'
		case 'Q':
		case 'q':
		case '/':
			if (a >= b)
			{
				result = a / b;
				printf("Manzoor :Division Of A = %d By B = %d Gives Quotient = %d !!!\n\n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Manzoor : Division Of B = %d By A = %d Gives Quotient = %d !!!\n\n", b, a, result);
			}
			break; // 'break' of case 'Q' or case 'q' or case '/'

	   // FALL THROUGH CONSITION FOR 'R' and 'r' and '%'
		case 'R':
		case 'r':
		case '%':
			if (a >= b)
			{
				result = a % b;
				printf("Manzoor :Division Of A = %d By B = %d Gives Remainder = %d !!!\n\n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Manzoor :Division Of B = %d By A = %d Gives Remainder = %d !!!\n\n", b, a, result);
			}
			break; // 'break' of case 'R' or case 'r' or case '%'

		default: // 'default' case for switch(optionDivision)
			printf("Manzoor :Invalid Character %c Entered For Division !!! Please Try Again...\n\n", optionDivision);
			break; // 'break' of 'default' of switch(optionDivision)

		} // Ending curly brace of switch(optionDivision)

		break; // 'break' of case 'D' or case 'd'

	default: // 'default' case for switch (option)
		printf("Manzoor :Invalid Character %c Entered !!! Please Try Again...\n\n", option);
		break;
	} // ending curly brace of switch(option)

	printf("Manzoor : Switch Case Block Complete !!!\n");

	return(0);
}
