#include<stdio.h>


int main (void)
{
struct MyData
{
	int i;
	float f;
	double d;
	char c;
}data={5,9.1f,3.78623,'N'};

	
	printf("\n\n DATA MEMBERS of 'struct MyData' Are : \n");
	printf("'i' = %d \n",data.i);
	printf("'f' = %f \n",data.f);
	printf("'d' = %lf \n",data.d);
	printf("'c' = %c \n\n",data.c);

	return(0);
}
