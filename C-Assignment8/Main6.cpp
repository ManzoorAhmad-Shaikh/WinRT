#include<stdio.h>

int main(){
	int i=0,j=0,k=0,s=0,n=0,l=0,m=0;
	
	printf("Enter the length of concentric rectangle\n");
	scanf("%d",&n);
	s=2*n-1;
	
	for(i=0;i<(s/2)+1;i++){
		m=n;
		for(j=0;j<i;j++){
			printf("%d ",m);
			m--;
		}
		
		for(k=0;k<s-2*i;k++){
			printf("%d ",n-i);
		}
		
		m=n-i+1;
		
		for(l=0;l<i;l++){
			printf("%d ",m);
			m++;
		}
		printf("\n");
	}
	
	for(i=s/2-1;i>=0;i--){
		m=n;
		for(j=0;j<i;j++){
			printf("%d ",m);
			m--;
		}
		
		for(k=0;k<s-2*i;k++){
			
			printf("%d ",n-i);
		}
		
		m=n-i+1;
		for(l=0;l<i;l++){
			printf("%d ",m);
			m++;
		}
		printf("\n");
	}
	
	return 0;
}