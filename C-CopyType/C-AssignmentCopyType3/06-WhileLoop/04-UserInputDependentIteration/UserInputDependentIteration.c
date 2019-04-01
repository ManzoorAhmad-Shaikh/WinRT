#include <stdio.h>
int main(void)
{
	//variable declarations
	int i_num, num, i;

	//code
	printf("\n\n");

	printf("Manzoor :Enter An Integer Value From Which Iteration Must Begin : ");
	scanf("%d", &i_num);

	printf("Manzoor :How Many Digits Do You Want To Print From %d Onwards ? : ", i_num);
	scanf("%d", &num);

	printf("Manzoor : Printing Digits %d to %d : \n\n", i_num, (i_num + num));

	i = i_num;
	while (i <= (i_num + num))
	{
		printf("\tManzoor :%d\n", i);
		i++;
	}

	printf("\n\n");

	return(0);
}
