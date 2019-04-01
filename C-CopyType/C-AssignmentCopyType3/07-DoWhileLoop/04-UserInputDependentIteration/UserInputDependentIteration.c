#include <stdio.h>
int main(void)
{
	//Variable declarations
	int iNum, num, i;

	//code
	printf("\n\n");

	printf("Manzoor :Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &iNum);

	printf("Manzoor : How Many Digits Do You Want To Print From %d Onwards  : ", iNum);
	scanf("%d", &num);

	printf("Manzoor: Printing Digits %d to %d : \n\n", iNum, (iNum + num));

	i = iNum;
	do
	{
		printf("\tManzoor: %d\n", i);
		i++;
	}while (i <= (iNum + num));

	printf("\n\n");

	return(0);
}
