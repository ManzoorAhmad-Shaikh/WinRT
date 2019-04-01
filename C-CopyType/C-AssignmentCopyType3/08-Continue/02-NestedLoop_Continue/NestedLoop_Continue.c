#include <stdio.h>
int main(void)
{
	//Variable declarations
	int i, j;

	//code
	printf("\n\n");

	printf("Manzoor :Outer Loop Prints Odd Numbers Between 1 and 10. \n\n");
	printf("Manzoor : Inner Loop Prints Even Numbers Between 1 and 10 For Every Odd Number Printed By Outer Loop. \n\n");

	
	for (i = 1; i <= 10; i++)
	{
		if (i % 2 != 0) //If number (i) Is Odd..
		{
			printf("Manzoor : i = %d\n", i);
			printf("--------------\n");
			for (j = 1; j <= 10; j++)
			{
				if (j % 2 == 0) //If number (j) Is even...
				{
					printf("\tManzoor : j = %d\n",j);
				}
				else //If number (j) Is Odd..
				{
					continue;
				}
			}
			printf("\n\n");
		}
		else //If Number (i) Is Even...
		{
			continue;
		}
	}

	printf("\n\n");

	return(0);
}
