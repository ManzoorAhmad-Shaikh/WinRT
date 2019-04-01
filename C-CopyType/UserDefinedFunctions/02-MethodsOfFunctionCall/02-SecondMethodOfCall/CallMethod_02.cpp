#include <stdio.h> 

int main(int argc, char *argv[], char *envp[])
{
	//function prototypes
	void display_information(void);
	void Function_Country(void); 
	display_information(); 
	Function_Country();
	return(0);
}

void display_information(void)
{
	//function prototypes
	void Function_My(void);
	void Function_Name(void);
	void Function_Is(void);
	void Function_FirstName(void);
	void Function_MiddleName(void);
	void Function_Surname(void);
	void Function_OfAMC(void); 


	Function_My();
	Function_Name();
	Function_Is();
	Function_FirstName();
	Function_MiddleName();
	Function_Surname();
	Function_OfAMC();
}

void Function_My(void) {
	//code
	printf("\n\n"); 
	printf("My"); 
}
void Function_Name(void)
{
	//code
	printf("\n\n"); 
		printf("Name");
}

void Function_Is(void){
	printf("\n\n"); 
	printf("Is");
}

void Function_FirstName(void){
	printf("\n\n"); 
	printf("Manzoor Ahmad"); 
}

void Function_MiddleName(void)	{
	printf("\n\n"); 
	printf("Farukh"); 
}

void Function_Surname(void)
{
	printf("\n\n"); 
	printf("Shaikh"); 
}

void Function_OfAMC(void) {
	printf("\n\n"); 
	printf("Of ASTROMEDICOMP");
}

void Function_Country(void){
	printf("\n\n"); 
	printf("I live In India.");
	printf("\n\n");
}
