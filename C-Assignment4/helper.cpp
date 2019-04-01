#include<stdio.h>

void factorialFor(int n){
	//variable declarations
	int i=0,fact=1;
	
	for(i=1;i<=n;i++){
		fact=i*fact;
	}
	printf("The factorial of given number : %d is %d using For Loop\n",n,fact);
}
void factorialWhile(int n){
	//variable declarations
	int i=1,fact=1;
	
	while(i<=n){
		fact=i*fact;
		i++;
	}
	printf("The factorial of given number : %d is %d using While Loop\n",n,fact);
}
void factorialDoWhile(int n){
	//variable declarations
	int i=1,fact=1;
	
	do{
		fact=i*fact;
		i++;
	}while(i<=n);
	printf("The factorial of given number : %d is %d using DoWhile Loop\n",n,fact);
}
int factorialRecursion(int n){
	//variable declarations
	if(n>=1){
		return(n*factorialRecursion(n-1));
	}
	else
	return 1;
}
void factorialWhileInfinite(int n){
	//variable declarations
	int i=1,fact=1;
	
	while(1){
		if(i<=n){
			fact=i*fact;
			i++;
		}else{
			break;
		}
	}
	printf("The factorial of given number : %d is %d\n using Infinite While Loop",n,fact);
}