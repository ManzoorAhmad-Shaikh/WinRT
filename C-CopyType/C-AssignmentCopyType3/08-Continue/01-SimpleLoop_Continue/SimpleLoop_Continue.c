#include <stdio.h>
int main(void)
{
	//Variable declarations
	int i;

	//code
	printf("\n\n");

	printf("Manzoor :Printing Even Numbers From 0 to 100: \n\n");

	for (i = 0; i <= 100; i++)
	{
		// Condition for a nuber to be even number => division of number by 2 leaves no remainder (remainder = 0)
		// If remainder is not 0, the number is odd number...
		if (i % 2 != 0) 
		{
			continue;
		}
		else
		{
			printf("\t Manzoor : %d\n", i);
		}
	}

	printf("\n\n");

	return(0);
}
