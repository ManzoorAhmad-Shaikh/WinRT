#include <stdio.h>
int main(void)
{
	//Variable declarations
	int num;

	//code
	printf("\n\n");

	printf("Manzoor : Enter Value For 'num' : ");
	scanf("%d", &num);

	// IF - ELSE - IF LADDER BEGINS FROM HERE...
	if (num < 0)
		printf("Manzoor : Num = %d Is Less Than 0 (NEGATIVE)\n\n", num);

	else if ((num > 0) && (num <= 100))
		printf("Manzoor : Num = %d Is Between 0 And 100\n", num);

	else if ((num > 100) && (num <= 200))
		printf("Manzoor : Num = %d Is Between 100 And 200\n\n", num);

	else if ((num > 200) && (num <= 300))
		printf("Manzoor :Num = %d Is Between 200 And 300\n\n", num);

	else if ((num > 300) && (num <= 400))
		printf("Manzoor : Num = %d Is Between 300 And 400\n\n", num);

	else if ((num > 400) && (num <= 500))
		printf("Manzoor : Num = %d Is Between 400 And 500\n\n", num);

	else if (num > 500)
		printf("Manzoor : Num = %d Is Greater Than 500 !!!\n\n", num);

	else // This IS THE TERMINATING 'ELSE' OF THIS 'IF - ELSE IF - ELSE' LADDER 
		printf("Manzoor :Invalid Value Entered \n\n");

	return(0);
}
