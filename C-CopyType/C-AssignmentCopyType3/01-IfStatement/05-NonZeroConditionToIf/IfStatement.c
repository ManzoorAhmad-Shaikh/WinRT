#include <stdio.h>
int main(void)
{
	//variable declarations
	int a;

	//Code
	printf("\n\n");

	a = 5;
	if (a) // Non-zero Positive Value
	{
		printf("Manzoor : if-block 1 : 'A' Exists And Has Value = %d !!!\n\n", a);
	}

	a = -5;
	if (a) // Non-zero Negative Value
	{
		printf(" Manzoor : if-block 2 : 'A' Exists And Has Value = %d !!!\n\n", a);
	}

	a = 0;
	if (a) // Zero Value
	{
		printf("Manzoor :if-block 3 : 'A' Exists And Has Value = %d !!!\n\n", a);
	}

	printf("Manzoor : All Three if-statements Are Done !!!\n\n");

	return(0);
}
