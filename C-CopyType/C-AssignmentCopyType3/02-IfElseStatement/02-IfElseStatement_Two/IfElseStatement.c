#include <stdio.h>
int main(void)
{
	//variable declarations
	int age;

	//code
	printf("\n\n");
	printf("Manzoor : Enter Age : ");
	scanf("%d", &age);
	printf("\n\n");
	if (age >= 18)
	{
		printf("Manzoor : Entering if-block...\n\n");
		printf("Manzoor : You Are Eligible For Voting \n\n");
	}
	else
	{
		printf("Manzoor :Entering else-block...\n\n");
		printf("Manzoor : You Are NOT Eligible For Voting\n\n");
	}
	printf("Manzoor Bye \n\n");
	return(0);
}
