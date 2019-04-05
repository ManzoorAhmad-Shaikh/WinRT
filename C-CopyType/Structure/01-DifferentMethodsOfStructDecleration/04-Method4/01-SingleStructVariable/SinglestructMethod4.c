#include<stdio.h>
#include<string.h>

	struct MyData
{
	int i;
	float f;
	double d;
};

int main(void)
{
    struct MyData data;
	int isize;
	int fsize;
	int dsize;
	int struct_MyData_size;
	
	data.i=30;
	data.f=11.45f;
	data.d=1.2995;
	
	printf("\n\n Data Members Of the Struct MyData Are : \n");
	printf("i = %d\n",data.i);
	printf("f = %f\n",data.f);
	printf("d = %lf\n",data.d);
	
	isize=sizeof(data.i);
	fsize=sizeof(data.f);
	dsize=sizeof(data.d);
	
	printf("\n\n Sizes (In Bytes) Of the Struct MyData Are : \n");
	printf("size of 'I' = %d\n",isize);
	printf("size of 'F' = %d\n",fsize);
	printf("size of 'D'  = %d\n",dsize);

	struct_MyData_size=sizeof(struct MyData);
	
	printf("\n\n");
	printf("Size of struct MyData : %d bytes",struct_MyData_size);
	
	return(0);
}

