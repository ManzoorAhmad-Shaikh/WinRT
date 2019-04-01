#include <stdio.h>
int main(void)
{
	//variable Declarations
	int i, j;

	//code
	printf("\n\n");

	printf("Manzoor :Printing Digits 1 to 10 and 10 to 100: \n\n");

	i = 1;
	j = 10;
	while (i <= 10, j <= 100)
	{
		printf("\t Manzoor :  %d \t %d\n", i, j);
		i++;
		j = j + 10;
	}

	printf("\n\n");

	return(0);
}
