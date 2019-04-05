#include<stdio.h>

struct MyData
{
	int	i;
	float f;
	double d;
};

struct MyData data;

int main(void)
{
	int isize;
	int fsize;
	int dsize;
	int MyData_size;
	
	data.i=30;
	data.f=11.45f;
	data.d=1.2995;
	
	printf("\n\n DATA MEMBERS OF 'struct MyData' Are : ");
	printf("\n 'i' = %d",data.i);
	printf("\n 'f' = %f",data.f);
	printf("\n 'd' = %lf",data.d);
	
	isize=sizeof(data.i);
	fsize=sizeof(data.f);
	dsize=sizeof(data.d);
	
	printf("\n\n SIZES OF Data Members of 'struct MyData' Are : ");
	printf("\n Size of 'i' = %d bytes",isize);
	printf("\n Size of 'f' = %d bytes" ,fsize);
	printf("\n Size of 'd' = %d bytes",dsize);

    MyData_size=sizeof(struct MyData);
	
	printf("\n\n Size of 'Struct MyData' : %d bytes",MyData_size); 

	return(0);
}
