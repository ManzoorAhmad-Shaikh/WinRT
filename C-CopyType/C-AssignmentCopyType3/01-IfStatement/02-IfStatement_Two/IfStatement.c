#include <stdio.h>
int main(void)
{
	//variable declarations
	int age;

	//code
	printf("\n\n");
	printf("Manzoor : Enter Age : ");
	scanf("%d", &age);
	if (age >= 18)
	{
		printf("Manzoor : You Are Eligible For Voting !!!\n\n");
	}
	return(0);
}

