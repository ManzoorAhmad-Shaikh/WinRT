#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
}data={30,4.5f,11.451995,'A'};

int main (void)
{
	printf("\n\n DATA MEMBERS of 'struct MyData' Are : \n");
	printf("'i' = %d \n",data.i);
	printf("'f' = %f \n",data.f);
	printf("'d' = %lf \n",data.d);
	printf("'c' = %c \n\n",data.c);

	return(0);
}
