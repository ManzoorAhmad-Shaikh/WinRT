#include <stdio.h>
int main(void)
{
	//Variable declaration
	float f;
	float f_num = 1.7f; 

	//code
	printf("\n\n");

	printf("Manzoor : Printing Numbers %f to %f : \n\n", f_num, (f_num * 10.0f));

	f = f_num;
	do
	{
		printf("\tManzoor :  %f\n", f);
		f = f + f_num;
	}while (f <= (f_num * 10.0f));

	printf("\n\n");

	return(0);
}
