#include<stdio.h>

int main(){
	//variable declarations
	int l=0,w[1000]={0},h[1000]={0},n=0,i=0;
	
	printf("Enter the length\n");
	scanf("%d",&l);
	printf("\nEnter the number of photos to be uploaded\n");
	scanf("%d",&n);
	
	printf("\nEnter the width and height of the photos\n");
	for(i=0;i<n;i++)
		scanf("%d %d",&w[i],&h[i]);
	
	printf("\nFollowing output\n");
	for(i=0;i<n;i++){
		if((w[i]==l)&&(h[i]==l))
			printf("Accepted\n");
		else if((w[i]>l)&&(h[i]>l))
			printf("Crop it\n");
		else 
			printf("Upload Another\n");
	}
	
	return(0);
}