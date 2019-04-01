#include<stdio.h>
#include"header.h"

int main(){
	//Variable declaration
	int n=0,fact=0;
	
	printf("Enter the number to find factorial\n");
	scanf("%d",&n);
	if(n>10)
		return 1;
	factorialFor(n);
	factorialWhile(n);
	factorialDoWhile(n);
	fact = factorialRecursion(n);
	printf("The factorial of given number : %d is %d using Recursion\n",n,fact);
	factorialWhileInfinite(n);
	
	return 0;

}