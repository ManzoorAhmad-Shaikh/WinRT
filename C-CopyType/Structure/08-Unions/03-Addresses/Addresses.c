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
	
	
	printf("\n\n  Members of Structure Are : ");
	
	s.i=9;
	s.f=8.7f;
	s.d=1.233422;
	s.c='P';
	
	
	printf("\n s.i = %d\n",s.i);
	printf("\n s.f = %f\n",s.f);
	printf("\n s.d = %lf\n",s.d);
	printf("\n s.c = %c\n",s.c);
	
	printf("Addresses Of Members of Struct Are : ");
	printf("\n s.i = %p\n",s.i);
	printf("\n s.f = %p\n",s.f);
	printf("\n s.d = %p\n",s.d);
	printf("\n s.c = %p\n",s.c);	
	
	printf("\n MyStruct s = %p \n",&s);

   	//Display u2
	printf("\n\n Members Of Union Are : ");
	
	u.i=3;
	printf("\n u.i = %d\n",u.i);
	
	u.f=4.5;
	printf("\n u.f = %f\n",u.f);
	
	u.d=5.12764;
	printf("\n u.d = %lf\n",u.d);
	
	u.c='A';
	printf("\n u.c = %c\n",u.c);
	
	printf("\n\n Addresses Of Union Are : ");
	printf("\n u.i =  %p\n",&u.i);
	printf("\n u.f =  %p\n",&u.f);
	printf("\n u.d =  %p\n",&u.d);
	printf("\n u.c =  %p\n",&u.c);
	
	printf("\n Union u = %p \n",&u);

	

	return(0);
}
