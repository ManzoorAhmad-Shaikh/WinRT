#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

struct MyData data={9,8.2f,9.61998,'P'};

int main (void)
{
	printf("\n\n DATA MEMBERS of 'struct MyData' Are : \n");
	printf("'i' = %d \n",data.i);
	printf("'f' = %f \n",data.f);
	printf("'d' = %lf \n",data.d);
	printf("'c' = %c \n\n",data.c);

	return(0);
}
