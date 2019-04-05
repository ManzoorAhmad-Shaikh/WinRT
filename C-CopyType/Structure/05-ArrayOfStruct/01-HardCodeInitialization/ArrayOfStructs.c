#include<stdio.h>
#include<string.h>

#define NLENGTH 100
#define MSTATUS 10

struct Employee
{
	char name[NLENGTH];
	int age;
	float salary;
	char sex;
	char marital_status[MSTATUS];	
};

int main(void)
{
	struct Employee ERecord[5];
	
	char employee_rajesh[]="Rajesh";
	char employee_sameer[]="Sameer";
	char employee_kalyani[]="Kalyani";
	char employee_sonali[]="Sonali";
	char employee_shantanu[]="Shantanu";
	
	int i;
	
	strcpy(ERecord[0].name,employee_rajesh);
	ERecord[0].age=30;
	ERecord[0].sex='M';
	ERecord[0].salary=50000.0f;
	strcpy(ERecord[0].marital_status, "Unmarried");

	strcpy(ERecord[1].name,employee_sameer);
	ERecord[1].age=32;
	ERecord[1].sex='M';
	ERecord[1].salary=60000.0f;
	strcpy(ERecord[1].marital_status, "Married");

	strcpy(ERecord[2].name,employee_kalyani);
	ERecord[2].age=29;
	ERecord[2].sex='F';
	ERecord[2].salary=62000.0f;
	strcpy(ERecord[2].marital_status, "Unmarried");

	strcpy(ERecord[3].name,employee_sonali);
	ERecord[3].age=33;
	ERecord[3].sex='F';
	ERecord[3].salary=40000.0f;
	strcpy(ERecord[3].marital_status, "Married");

	strcpy(ERecord[4].name,employee_shantanu);
	ERecord[4].age=35;
	ERecord[4].sex='M';
	ERecord[4].salary=55000.0f;
	strcpy(ERecord[4].marital_status, "Married");

	//Display
	printf("\n\n ****** DISPLAYING EMPLOYEE RECORD *****\n\n");
	for(i=0;i<5;i++)
	{
		printf("****** EMPLOYEE NUMBER %d ******\n\n", (i + 1));
		printf("Name           : %s\n", ERecord[i].name);
		printf("Age            : %d years\n", ERecord[i].age);

		if (ERecord[i].sex == 'M' || ERecord[i].sex == 'm')
			printf("Sex            : Male\n");
		else
			printf("Sex            : Female\n");

		printf("Salary         : Rs. %f\n", ERecord[i].salary);
		printf("Marital Status : %s\n", ERecord[i].marital_status);

		printf("\n\n");
	}

return(0);

}
