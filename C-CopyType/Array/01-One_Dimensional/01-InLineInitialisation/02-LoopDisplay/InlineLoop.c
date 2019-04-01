#include<stdio.h>

int main(void)
{
	int iArray[]={9,30,6,12,98,95,20,23,2,45};
	int int_size;
	int iArray_size;
	int iArray_num_elements;
	
	float fArray[]={1.2f,2.3f,3.4f,4.5f,5.6f,6.7f,7.8f,8.9f};
	int float_size;
	int fArray_size;
	int fArray_num_elements;
	
	char cArray[]={'A','S','T','R','O','M','E','D','I','C','O','M','P'};
	int char_size;
	int cArray_size;
	int cArray_num_elements;

	int i;
		
	//code
	printf("\n\n");
	printf("\n\n In-Line Initialization And Loop Display of Elements of Array 'iArray[]': ");
	
	
	int_size=sizeof(int);
	iArray_size=sizeof(iArray);
	iArray_num_elements=iArray_size/int_size;
	
	for(i=0;i<iArray_num_elements;i++)
	{
		printf("\n iArray[%d] ( Element %d) = %d\n",i,(i+1),iArray[i]);
	}
	
	printf("\n\n Size of data type 'Int' = %d bytes \n",int_size);
	printf("\n Number of Elements in 'iArray' = %d ",iArray_num_elements);
	printf("\n Size of 'iArray' (%d Elements * %d Bytes) = %d Bytes",iArray_num_elements,int_size,iArray_size);


	//fArray
	printf("\n\n");
	printf("\n\n In-Line Initialization And Loop Display of Elements of Array 'fArray[]': ");
	
	float_size=sizeof(float);
	fArray_size=sizeof(fArray);
	fArray_num_elements=fArray_size/float_size;
	
	for(i=0;i<fArray_num_elements;i++)
	{
		printf("\n fArray[%d] ( Element %d) = %f\n",i,(i+1),fArray[i]);
	}
	
	printf("\n\n Size of data type 'Float'                   = %d  bytes \n",float_size);
	printf("\n Number of Elements in 'fArray'              = %d ",fArray_num_elements);
	printf("\n Size of 'fArray' (%d Elements * %d Bytes)   = %d Bytes",fArray_num_elements,float_size,fArray_size);


	//*********cArray
	printf("\n\n");
	printf("\n\n In-Line Initialization And Loop Display of Elements of Array 'cArray[]': ");
	
	char_size=sizeof(char);
	cArray_size=sizeof(cArray);
	cArray_num_elements=cArray_size/char_size;

	for(i=0;i<cArray_num_elements;i++)
	{
		printf("\n cArray[%d] ( Element %d) = %c\n",i,(i+1),cArray[i]);
	}

	printf("\n\n Size of data type 'Char' = %d bytes \n",char_size);
	printf("\n Number of Elements in 'cArray' = %d ",cArray_num_elements);
	printf("\n Size of 'cArray' (%d Elements * %d Bytes) = %d Bytes",cArray_num_elements,char_size,cArray_size);

	
	return(0);	
}
