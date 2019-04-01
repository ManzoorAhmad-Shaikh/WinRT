#include <stdio.h>
int main(void)
{
	//Variable declarations
	int i, j, k;

	//code
	printf("\n\n");
	
	i = 1;
	do
	{
		printf("Manzoor :i = %d\n", i);
		printf("--------------\n\n");
		
		j = 1;
		do
		{
			printf("\tManzoor j = %d\n", j);
			printf("\t-------------------\n\n");
			
			k = 1;
			do
			{
				printf("\t\tManzoor :k = %d\n", k);
				k++;
			}while (k <= 3);
			printf("\n\n");
			j++;
		}while (j <= 5);
		printf("\n\n");
		i++;
	}while (i <= 10);
	return(0);
}
