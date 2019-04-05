#include<stdio.h>
#include<string.h>

#define NEMPLOYEE 5

#define NLENGTH 100
//#define MSTATUS 10

struct Employee
{
	char name[NLENGTH];
	int age;
	float salary;
	char sex;
	char marital_status;	
};

int main(void)
{
	//fun declaration
	void MyGetString(char[],int);
	
	struct Employee ERecord[NEMPLOYEE];
	int i;
	
	for(i=0;i<NEMPLOYEE;i++)
	{
			printf("\n\n ****** DATA ENTRY EMPLOYEE RECORD *****\n\n");
					
					printf("\n\n ");
					printf("\n Enter Employee Name : ");
					MyGetString(ERecord[i].name,NLENGTH);
					
					printf("\n\n Enter Employee's Age (in years) : ");
					scanf("%d",&ERecord[i].age);
					
					printf("\n\n Enter Employee's Sex : ");
					ERecord[i].sex=getch();
					printf("%c",ERecord[i].sex);
					ERecord[i].sex=toupper(ERecord[i].sex);
					
					printf("\n\n Enter Employee's salary (in Indian Rupee) : ");
					scanf("%f",&ERecord[i].salary);
					
					printf("\n\n Enter Employee's Marital Status : ");
					//scanf("%c",&ERecord[i].marital_status);
					ERecord[i].marital_status=getch();
					printf("%c",ERecord[i].marital_status);
					ERecord[i].marital_status=toupper(ERecord[i].marital_status);
					
	}
					
					
					
	
	//Display
	printf("\n\n ****** DISPLAYING EMPLOYEE RECORD *****\n\n");
	for(i=0;i<5;i++)
	{
		printf("****** EMPLOYEE NUMBER %d ******\n\n", (i + 1));
		printf("Name                  : %s\n", ERecord[i].name);
		printf("Age                   : %d years\n", ERecord[i].age);

		if (ERecord[i].sex == 'M' || ERecord[i].sex == 'm')
			printf("Sex               : Male\n");
		else if(ERecord[i].sex == 'F' || ERecord[i].sex == 'f')
			printf("Sex               : Female\n");
		else
			printf("Sex               :Invalid Data Entered");	

		printf("Salary         : Rs. %f\n", ERecord[i].salary);
		if (ERecord[i].marital_status == 'Y' )
			printf("Marital Status         : Married\n");
		else if(ERecord[i].marital_status == 'N' )
			printf("Marital Status         : Unmareied\n");
		else
			printf("Marital Status            :Invalid Data Entered");	
		//printf("Marital Status : %s\n", ERecord[i].marital_status);

		printf("\n\n");
	}

return(0);

}
void MyGetString(char str[], int str_size)
{
	//variable declarations
	int i;
	char ch = '\0';

	//code
	i = 0;
	do
	{
		ch = getch();
		str[i] = ch;
		printf("%c", str[i]);
		i++;
	}while ((ch != '\r') && (i < str_size));
	
	if (i == str_size)
		str[i - 1] = '\0';
	else
		str[i] = '\0';
}

