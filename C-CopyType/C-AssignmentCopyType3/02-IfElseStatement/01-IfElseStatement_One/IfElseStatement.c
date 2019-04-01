#include <stdio.h>
int main(void)
{
	//Variable declarations
	int a, b, p;

	//code
	a = 9;
	b = 30;
	p = 30;

	// FIRST if-else PAIR 
	printf("\n\n");
	if (a < b)
	{
		printf("Manzoor : Entering First if-block...\n\n");
		printf("Manzoor : A Is Less Than B !!!\n\n");
	}
	else
	{
		printf("Manzoor : Entering First else-block...\n\n");
		printf("Manzoor : A Is NOT Less Than B !!!\n\n");
	}
	printf("Manzoor :First if-else Pair Done !!!\n\n");

	// SECOND if-else PAIR
	printf("\n\n");
	if (b != p)
	{
		printf("Manzoor :Entering Second if-block...\n\n");
		printf("Manzoor : B Is NOT Equal To P !!!\n\n");
	}
	else
	{
		printf("Manzoor : Entering Second else-block...\n\n");
		printf("Manzoor : B Is Equal To P !!!\n\n");
	}
	printf("Manzoor : Second if-else Pair Done !!!\n\n");
		
	return(0);
}
