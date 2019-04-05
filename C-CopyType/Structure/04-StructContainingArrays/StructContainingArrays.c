#include<stdio.h>
#include<string.h>

#define INT 10
#define FLOAT 5
#define CHAR 26

#define NSTRINGS 10
#define MAX_STRINGS 20

#define ALPHABET_BEGINNING 65

struct MyDataOne
{
	int iArray[INT];
	float fArray[FLOAT];
};

struct MyDataTwo
{
	char cArray[CHAR];
	char strArray[NSTRINGS][MAX_STRINGS];
};

int main(void)
{
	struct MyDataOne data_one;
	struct MyDataTwo data_two;
	int i;
	
	//code
	data_one.fArray[0]=0.1f;
	data_one.fArray[1]=1.2f;
	data_one.fArray[2]=2.3f;
	data_one.fArray[3]=3.4f;
	data_one.fArray[4]=4.5f;
	
	printf("\n\n Enter %d Integers : \n",INT);
	for(i=0;i<INT;i++)
	{
		scanf("%d",&data_one.iArray[i]);
	}
	
	for(i=0;i<CHAR;i++)
	{
		data_two.cArray[i]=(char)(i+ALPHABET_BEGINNING);
	}
	
	strcpy(data_two.strArray[0],"Welcome !!");
	strcpy(data_two.strArray[1],"This ");
	strcpy(data_two.strArray[2],"Is ");
	strcpy(data_two.strArray[3],"ASTROMEDICOMP'S");
	strcpy(data_two.strArray[4],"Real ");
	strcpy(data_two.strArray[5],"Time ");
	strcpy(data_two.strArray[6],"Rendering ");
	strcpy(data_two.strArray[7],"Batch ");
	strcpy(data_two.strArray[8],"Of ");
	strcpy(data_two.strArray[9],"2018-19-20");

	//Display
	
	printf("\n\n Integer Array (data_one.iArray[]) : \n\n");
	for (i = 0; i < INT; i++)
		printf("data_one.iArray[%d] = %d\n", i, data_one.iArray[i]);


	printf("\n\n Floating-Point Array (data_one.fArray[]) : \n\n");
	for (i = 0; i < FLOAT; i++)
		printf("data_one.fArray[%d] = %f\n", i, data_one.fArray[i]);



	printf("\n\n Members Of 'struct DataTwo' Alongwith Their Assigned Values Are : \n\n");


	printf("\n\n Character Array (data_two.cArray[]) : \n\n");
	for (i = 0; i < CHAR; i++)
		printf("data_two.cArray[%d] = %c\n", i, data_two.cArray[i]);


	printf("\n\n String Array (data_two.strArray[]) : \n\n");
	for (i = 0; i < NSTRINGS; i++)
		printf("%s ", data_two.strArray[i]);

	printf("\n\n");
	
	return(0);
}
