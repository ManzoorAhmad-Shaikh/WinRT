#include<stdio.h>

void ChangeCase(char *);
int main(){
	//variable declarations
	
	char str[1000]={'\0'};
	
	printf("Enter the string\n");
	scanf("%[^\n]%*c",str);
	
	printf("Before changing the case of string : %s\n",str);
	
	ChangeCase(str);
	printf("After changing the case of string : %s\n",str);
	
	return(0);
}

void ChangeCase(char *str){
	
	//code
	
	while(*str!='\0'){
		if(*str>='A' && *str<='Z')
			*str=*str+32;
		else if(*str>='a' && *str<='z')
			*str=*str-32;
		else{}
		str++;
	}
}