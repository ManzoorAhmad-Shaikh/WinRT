#include<stdio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

int main(void)
{
	struct MyData data;
	
	data.i=30;
	data.f=11.45f;
	data.d=1.2995;
	data.c='A';
	
	//Display
	printf("DATA MEMBERS of 'struct MyData' Are : ");
	printf("i = %d\n",data.i);
	printf("f = %f\n",data.f);
	printf("d = %lf\n",data.d);
	printf("c = %c\n",data.c);
	
	printf("ADDRESSES DATA MEMBERS of 'struct MyData' Are : ");
	printf("i Occupies addresses from  %p\n",&data.i);
	printf("f Occupies addresses from  %p\n",&data.f);
	printf("d Occupies addresses from  %p\n",&data.d);
	printf("c Occupies addresses from  %p\n",&data.c);
	
	printf("Starting Address of 'struct MyData' variable 'data' = %p \n",&data);
	
	return(0);
}
