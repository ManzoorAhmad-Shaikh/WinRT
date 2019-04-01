#include<stdio.h>
#include<stdlib.h>		

int main(void){
	//variable
	int **ptr = NULL;
	int i=0;
	
	ptr = (int **)malloc(5 * sizeof(int *));
	
	if(ptr == NULL){
		return 1;
	}
	
	for(i = 0;i<5;i++){
		ptr[i] = (int *)malloc(3* sizeof(int));
	}
	
	printf("%p ",ptr);
	printf("%p ",(ptr+1));
	printf("%p ",(ptr+2));
	printf("%p ",(ptr+3));
	printf("%p ",(ptr+0));
	
	for(i = 0 ;i<5;i++){
		free(ptr[i]);
			
	}
	free(ptr);
	//ptr = NULL;
	
	return 0;
}