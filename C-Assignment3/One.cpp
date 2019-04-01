#include<stdio.h>

void PrintAllPrimeNumbers(int);

int main(){
	//Variable declarations
	int n=0,b=0;
	
	//code
	printf("Enter a Number\n");
	scanf("%d",&n);
	
	if(n<=0 || n>1000){
		printf("Enter the number in between 1 to 1000\n");
		return 1;
	}
	PrintAllPrimeNumbers(n);
}

void PrintAllPrimeNumbers(int n){
	int i=0,j=0,fact=0;
	printf("The prime number is : ");
	//code
	for(i=1;i<=n;i++){
		fact=0;
		for(j=1;j<=n;j++){
			if(i%j==0)
			fact++;
		}
		if(fact==2)
			printf("%d ",i);
	}
}