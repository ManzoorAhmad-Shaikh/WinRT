#include <stdio.h>
int main(void)
{
	//Variable declarations
	int i, j;

	//code
	printf("\n\n");

	i = 1;
	do
	{
		printf("Manzoor: i = %d\n", i);
		printf("-------------\n\n");
		
		j = 1;
		do
		{
			printf("\tManzoor :j = %d\n", j);
			j++;
		}while (j <= 5);
		i++;
		printf("\n\n");
	}while (i <= 10);
	return(0);
}
