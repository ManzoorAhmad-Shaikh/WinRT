#include<stdio.h>
#include<conio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char ch;
};


int main (void)
{
	struct MyData data;
	
	printf("\n\n Enter Int value for Data Member 'i' of 'MyData' : ");
	scanf("%d",&data.i);
	
	printf("\n\n Enter Float value for Data Member 'f' of 'MyData' : ");
	scanf("%f",&data.f);
	
	printf("\n\n Enter Double value for Data Member 'd' of 'MyData' : ");
	scanf("%lf",&data.d);
	
	printf("\n\n Enter Char value for Data Member 'c' of 'MyData' : ");
	data.ch=getch();
	
	
	printf("\n\n DATA MEMBERS of 'struct MyData' Are : \n");
	printf("'i' = %d \n",data.i);
	printf("'f' = %f \n",data.f);
	printf("'d' = %lf \n",data.d);
	printf("'c' = %c \n\n",data.ch);

	return(0);
}
