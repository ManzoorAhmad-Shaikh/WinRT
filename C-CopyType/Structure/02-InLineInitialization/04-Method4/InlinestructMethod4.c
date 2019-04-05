#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};


int main (void)
{
	struct MyData data_one={35,3.9f,1.23765,'A'};
	
	struct MyData data_two={'P',6.2f,12.199523,68};
	
	struct MyData data_three={36,'G'};
	
	struct MyData data_four={79};
	
	printf("\n\n DATA MEMBERS of 'struct MyData data_one' Are : \n");
	printf("'i' = %d \n",data_one.i);
	printf("'f' = %f \n",data_one.f);
	printf("'d' = %lf \n",data_one.d);
	printf("'c' = %c \n\n",data_one.c);

	printf("\n\n DATA MEMBERS of 'struct MyData data_two' Are : \n");
	printf("'i' = %d \n",data_two.i);
	printf("'f' = %f \n",data_two.f);
	printf("'d' = %lf \n",data_two.d);
	printf("'c' = %c \n\n",data_two.c);

	printf("\n\n DATA MEMBERS of 'struct MyData data_three' Are : \n");
	printf("'i' = %d \n",data_three.i);
	printf("'f' = %f \n",data_three.f);
	printf("'d' = %lf \n",data_three.d);
	printf("'c' = %c \n\n",data_three.c);

	printf("\n\n DATA MEMBERS of 'struct MyData data_four' Are : \n");
	printf("'i' = %d \n",data_four.i);
	printf("'f' = %f \n",data_four.f);
	printf("'d' = %lf \n",data_four.d);
	printf("'c' = %c \n\n",data_four.c);


	return(0);
}
