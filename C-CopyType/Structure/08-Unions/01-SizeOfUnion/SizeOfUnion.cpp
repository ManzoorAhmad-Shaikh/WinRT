#include<stdio.h>

struct MyStruct
{
	int i;
	float f;
	double d;
	char c;
};


union MyUnion
{
	int i;
	float f;
	double d;
	char c;
};

int main(void)
{
	struct MyStruct s;
	union MyUnion u;
	
	
	printf("\n\n Size of 'MyStruct' is = %d \n",sizeof(s));
	printf("\n\n Size of 'MyUnion' is = %d \n",sizeof(u));
	

	return(0);
}
