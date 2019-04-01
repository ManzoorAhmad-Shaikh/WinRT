#include<stdio.h>
int main(void)
{
	int iArrayOne[10];
	int iArrayTwo[10];
	
	//code
	iArrayOne[0]=3;
	iArrayOne[1]=6;
	iArrayOne[2]=9;
	iArrayOne[3]=12;
	iArrayOne[4]=15;
	iArrayOne[5]=18;
	iArrayOne[6]=21;
	iArrayOne[7]=24;
	iArrayOne[8]=27;
	iArrayOne[9]=30;
	
	printf("\n\n");
	printf("\n 1st Element of Array = %d\n",iArrayOne[0]);
	printf("\n 2nd Element of Array = %d\n",iArrayOne[1]);
	printf("\n 3rd Element of Array = %d\n",iArrayOne[2]);
	printf("\n 4th Element of Array = %d\n",iArrayOne[3]);
	printf("\n 5th Element of Array = %d\n",iArrayOne[4]);
	printf("\n 6th Element of Array = %d\n",iArrayOne[5]);
	printf("\n 7th Element of Array = %d\n",iArrayOne[6]);
	printf("\n 8th Element of Array = %d\n",iArrayOne[7]);
	printf("\n 9th Element of Array = %d\n",iArrayOne[8]);
	printf("\n 10th Element of Array = %d\n",iArrayOne[9]);
	
	//**********ArrayTwo
	
	printf("\n\n");
	
	printf("\n Enter 1st Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[0]);
	printf("\n Enter 2nd Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[1]);
	printf("\n Enter 3rd Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[2]);	
	printf("\n Enter 4th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[3]);	
	printf("\n Enter 5th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[4]);	
	printf("\n Enter 6th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[5]);	
	printf("\n Enter 7th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[6]);
	printf("\n Enter 8th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[7]);	
	printf("\n Enter 9th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[8]);	
	printf("\n Enter 10th Element Of 'iArrayTwo[]' : ");
	scanf("%d",&iArrayTwo[9]);
		
printf("\n\n");
	printf("\n Piece-meal (User Input) Assignment And Display Of Elements to Array 'iArrayTwo[]' : \n");
	printf("\n 1st Element Of Array 'iArrayTwo[]' Or Element At 0th Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[0]);
	printf("\n 2nd Element Of Array 'iArrayTwo[]' Or Element At 1st Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[1]);
	printf("\n 3rd Element Of Array 'iArrayTwo[]' Or Element At 2nd Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[2]);
	printf("\n 4th Element Of Array 'iArrayTwo[]' Or Element At 3rd Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[3]);
	printf("\n 5th Element Of Array 'iArrayTwo[]' Or Element At 4th Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[4]);
	printf("\n 6th Element Of Array 'iArrayTwo[]' Or Element At 5th Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[5]);
	printf("\n 7th Element Of Array 'iArrayTwo[]' Or Element At 6th Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[6]);
	printf("\n 8th Element Of Array 'iArrayTwo[]' Or Element At 7th Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[7]);
	printf("\n 9th Element Of Array 'iArrayTwo[]' Or Element At 8th Index Of Array 'iArrayTwo[]' = %d\n", iArrayTwo[8]);
	printf("\n 10th Element Of Array 'iArrayTwo[]' Or Element At 9th Index Of Array 'iArrayTwo[]' = %d\n\n", iArrayTwo[9]);		
		
	return(0);
}
