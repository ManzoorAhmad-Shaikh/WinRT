#include<stdio.h>

struct MyUnion
{
	int i;
	float f;
	double d;
	char c;
};

int main(void)
{
	struct MyUnion u1,u2;
	
	u1.i=6;
	u1.f=1.2f;
	u1.d=8.333333;
	u1.c='S';
	
	//Display u1
	printf("\n\n DATA MEMBERS of 'MyUnion u1' Are : ");
	printf("\n i = %d\n",u1.i);
	printf("\n f = %f\n",u1.f);
	printf("\n d = %lf\n",u1.d);
	printf("\n c = %c\n",u1.c);
	
	printf("ADDRESSES DATA MEMBERS of 'MyUnion u1' Are : ");
	printf("\n u1.i =  %p\n",&u1.i);
	printf("\n u1.f = %p\n",&u1.f);
	printf("\n u1.d =  %p\n",&u1.d);
	printf("\n u1.c =  %p\n",&u1.c);
	
	printf("\n MyUnion u1 = %p \n",&u1);

   	//Display u2
	printf("\n\n DATA MEMBERS of 'MyUnion u2' Are : ");
	u2.i=3;
	printf("\n i = %d\n",u2.i);
	
	u2.f=4.5;
	printf("\n f = %f\n",u2.f);
	
	u2.d=5.12764;
	printf("\n d = %lf\n",u2.d);
	
	u2.c='D';
	printf("\n c = %c\n",u2.c);
	
	printf("ADDRESSES DATA MEMBERS of 'MyUnion u2' Are : ");
	printf("\n u2.i =  %p\n",&u2.i);
	printf("\n u2.f =  %p\n",&u2.f);
	printf("\n u2.d =  %p\n",&u2.d);
	printf("\n u2.c =  %p\n",&u2.c);
	
	printf("\n MyUnion u2 = %p \n",&u2);

	
	return(0);
}
