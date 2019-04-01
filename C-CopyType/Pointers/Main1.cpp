#include<stdio.h>
#include<stdlib.h>		

int main(void){
	//variable
	int *a[5];
	int i=0;
	
	a[0] = (int *)malloc(3 *sizeof(int)); 
	for(i = 1;i<5;i++){
		a[i] = (int *)malloc(3* sizeof(int));
	}
	
	printf("%p ",a);
	printf("%p ",(a[1]));
	printf("%p ",(a[2]));
	printf("%p ",(a[3]));
	printf("%p ",(a[4]));
	
	
	return 0;
}