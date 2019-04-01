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
	
	//code
	//*****iArray
	printf("\n\n");
	printf("\n\n In-Line Initialization And Peace-Meal Display of Elements of Array 'iArray[]': ");
	printf("\n iArray[1] (1st Element) = %d\n",iArray[0]);
	printf("\n iArray[2] (2nd Element) = %d\n",iArray[1]);
	printf("\n iArray[3] (3rd Element) = %d\n",iArray[2]);
	printf("\n iArray[4] (4th Element) = %d\n",iArray[3]);
	printf("\n iArray[5] (5th Element) = %d\n",iArray[4]);
	printf("\n iArray[6] (6th Element) = %d\n",iArray[5]);
	printf("\n iArray[7] (7th Element) = %d\n",iArray[6]);
	printf("\n iArray[8] (8th Element) = %d\n",iArray[7]);
	printf("\n iArray[9] (9th Element) = %d\n",iArray[8]);
	printf("\n iArray[10] (10th Element) = %d\n",iArray[9]);
	
	int_size=sizeof(int);
	iArray_size=sizeof(iArray);
	iArray_num_elements=iArray_size/int_size;
	printf("\n Size of data type 'Int' = %d bytes \n",int_size);
	printf("\n Number of Elements in 'iArray' = %d ",iArray_num_elements);
	printf("\n Size of 'iArray' (%d Elements * %d Bytes) = %d Bytes",iArray_num_elements,int_size,iArray_size);

	//Array
	printf("\n\n");
	printf("\n\n In-Line Initialization And Peace-Meal Display of Elements of Array 'fArray[]': ");
	printf("\n fArray[1] (1st Element) = %f\n",fArray[0]);
	printf("\n fArray[2] (2nd Element) = %f\n",fArray[1]);
	printf("\n fArray[3] (3rd Element) = %f\n",fArray[2]);
	printf("\n fArray[4] (4th Element) = %f\n",fArray[3]);
	printf("\n fArray[5] (5th Element) = %f\n",fArray[4]);
	printf("\n fArray[6] (6th Element) = %f\n",fArray[5]);
	printf("\n fArray[7] (7th Element) = %f\n",fArray[6]);
	printf("\n fArray[8] (8th Element) = %f\n",fArray[7]);
	printf("\n fArray[9] (9th Element) = %f\n",fArray[8]);
	printf("\n fArray[10] (10th Element) = %f\n",fArray[9]);
	
	float_size=sizeof(float);
	fArray_size=sizeof(fArray);
	fArray_num_elements=fArray_size/float_size;
	printf("\n Size of data type 'Float'                   = %d  bytes \n",float_size);
	printf("\n Number of Elements in 'fArray'              = %d ",fArray_num_elements);
	printf("\n Size of 'fArray' (%d Elements * %d Bytes)   = %d Bytes",fArray_num_elements,float_size,fArray_size);

	//*******cArray
	printf("\n\n");
	printf("\n\n In-Line Initialization And Peace-Meal Display of Elements of Array 'cArray[]': ");
	printf("\n cArray[1] (1st Element) = %c\n",cArray[0]);
	printf("\n cArray[2] (2nd Element) = %c\n",cArray[1]);
	printf("\n cArray[3] (3rd Element) = %c\n",cArray[2]);
	printf("\n cArray[4] (4th Element) = %c\n",cArray[3]);
	printf("\n cArray[5] (5th Element) = %c\n",cArray[4]);
	printf("\n cArray[6] (6th Element) = %c\n",cArray[5]);
	printf("\n cArray[7] (7th Element) = %c\n",cArray[6]);
	printf("\n cArray[8] (8th Element) = %c\n",cArray[7]);
	printf("\n cArray[9] (9th Element) = %c\n",cArray[8]);
	printf("\n cArray[10] (10th Element) = %c\n",cArray[9]);
	printf("\n cArray[11] (11th Element) = %c\n", cArray[10]);
	printf("\n cArray[11] (12th Element) = %c\n", cArray[11]);
	printf("\n cArray[12] (13th Element) = %c\n\n", cArray[12]);
	
	char_size=sizeof(char);
	cArray_size=sizeof(cArray);
	cArray_num_elements=cArray_size/char_size;
	printf("\n Size of data type 'Char' = %d bytes \n",char_size);
	printf("\n Number of Elements in 'cArray' = %d ",cArray_num_elements);
	printf("\n Size of 'cArray' (%d Elements * %d Bytes) = %d Bytes",cArray_num_elements,char_size,cArray_size);

	
	return(0);	
}
