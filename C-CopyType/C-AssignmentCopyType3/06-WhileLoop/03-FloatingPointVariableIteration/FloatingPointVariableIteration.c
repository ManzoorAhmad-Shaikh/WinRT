#include <stdio.h>
int main(void)
{
	//variable declarations
	float f;
	float f_num = 1.7f; //simply change this value ONLY to get different outputs...

	//code
	printf("\n\n");

	printf("Manzoor : Printing Numbers %f to %f : \n\n", f_num, (f_num * 10.0f));

	f = f_num;
	while(f <= (f_num * 10.0f))
	{
		printf("\tManzoor :%f\n", f);
		f = f + f_num;
	}

	printf("\n\n");

	return(0);
}
