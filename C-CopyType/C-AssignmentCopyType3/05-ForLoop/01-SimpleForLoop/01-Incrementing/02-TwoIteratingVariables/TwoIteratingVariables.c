#include <stdio.h>
int main(void)
{
	//variable declarations
	int i, j;

	//code
	printf("\n\n");

	printf("Manzoor :Printing Digits 1 to 10 and 10 to 100 : \n\n");

	for (i = 1, j = 10; i <= 10, j <= 100; i++, j = j + 10)
	{
		printf("\t Manzoor : %d \t %d\n", i, j);
	}

	printf("\n\n");

	return(0);
}
