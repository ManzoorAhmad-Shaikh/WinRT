#include<stdio.h>
#include<stdlib.h>		

int main(void){
	//variable
	int a[5][3];
	int i=0,j=0;
	
	for(i = 0;i < 5; i++){
		for(j = 0;j < 3;j++){
			scanf("%d",&a[i][j]);
			//printf("\n");
		}
	}
	
	
	for(i = 0;i < 5; i++){
		for(j = 0;j < 3;j++){
			printf("%d",a[i][j]);
			printf("\t");
			printf("%p",&a[i][j]);
			printf("\t");
		}
		printf("\n\n");
	}
	
	
	return 0;
}