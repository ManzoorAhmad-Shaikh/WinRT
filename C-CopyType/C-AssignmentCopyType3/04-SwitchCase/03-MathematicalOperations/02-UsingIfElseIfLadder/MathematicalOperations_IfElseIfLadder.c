#include <stdio.h> 
#include <conio.h> 

int main(void)
{
	//Variable declarations
	int a, b;
	int result;

	char option, optionDivision;

	//code
	printf("\n\n");

	printf("Manzoor : Enter Value For 'A' : ");
	scanf("%d", &a);

	printf("Manzoor :Enter Value For 'B' : ");
	scanf("%d", &b);

	printf("Manzoor :Enter Option In Character : \n\n");
	printf("Manzoor : 'A' or 'a' For Addition : \n");
	printf("Manzoor : 'S' or 's' For Subtraction : \n");
	printf("Manzoor :'M' or 'm' For Multiplication : \n");
	printf("Manzoor :'D' or 'd' For Division : \n\n");

	printf("Manzoor : Enter Option : ");
	option = getch();

	printf("\n\n");

	if (option == 'A' || option == 'a')
	{
		result = a + b;
		printf("Manzoor :Addition Of A = %d And B = %d Gives Result %d !!!\n\n", a, b, result);
	}

	else if (option == 'S' || option == 's')
	{
		if (a >= b)
		{
			result = a - b;
			printf("Manzoor :Subtraction Of B = %d From A = %d Gives Result %d !!!\n\n", b, a, result);
		}
		else
		{
			result = b - a;
			printf("Manzoor :Subtraction Of A = %d From B = %d Gives Result %d !!!\n\n", a, b, result);
		}
	}

	else if(option == 'M' || option == 'm')
	{
		result = a * b;
		printf("Manzoor :Multiplication Of A = %d And B = %d Gives Result %d !!!\n\n", a, b, result);
	}
	
	else if (option == 'D' || option == 'd')
	{
		printf("Manzoor : Enter Option In Character : \n\n");
		printf("Manzoor : 'Q' or 'q' or '/' For Quotient Upon Division : \n");
		printf("Manzoor :'R' or 'r' or '%%' For Remainder Upon Division : \n");

		printf("Manzoor : Enter Option : ");
		optionDivision = getch();

		printf("\n\n");
		
		if (optionDivision == 'Q' || optionDivision == 'q' || optionDivision == '/')
		{
			if (a >= b)
			{
				result = a / b;
				printf("Manzoor : Division Of A = %d By B = %d Gives Quotient = %d !!\n\n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Manzoor :Division Of B = %d By A = %d Gives Quotient = %d !\n\n", b, a, result);
			}
		}

		else if (optionDivision == 'R' || optionDivision == 'r' || optionDivision == '%')
		{
			if (a >= b)
			{
				result = a % b;
				printf("Manzoor : Division Of A = %d By B = %d Gives Remainder = %d !\n\n", a, b, result);
			}
			else
			{
				result = b / a;
				printf("Manzoor :Division Of B = %d By A = %d Gives Remainder = %d !\n\n", b, a, result);
			}
		}
		
		else
			printf("Manzoor :Invalid Character %c Entered For Division. Please Try Again.\n\n", optionDivision);
	}

	else
		printf("Manzoor : Invalid Character %c Entered . Please Try Again.\n\n", option);

	printf("Manzoor : If - Else If - Else Ladder Complete !!!\n");

	return(0);
}
