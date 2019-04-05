#include<stdio.h>
#include<conio.h>

struct MyData
{
	int i;
	float f;
	double d;
	char c;
};

int main(void)
{
	struct MyData AddStructMembers(struct MyData,struct MyData,struct MyData);
	
	struct MyData d1,d2,d3,answer_data;
	
	printf("\n\n\n\n ");
	printf("******* DATA 1 *******");
	printf("\n Enter Integer Value for 'i' of 'struct MyData d1' : ");
	scanf("%d",&d1.i);

	printf("\n\n Enter Float Value for 'f' of 'struct MyData d1' : ");
	scanf("%f",&d1.f);

	printf("\n\n Enter Double Value for 'd' of 'struct MyData d1' : ");
	scanf("%lf",&d1.i);

	printf("\n\n Enter Char Value for 'c' of 'struct MyData d1' : ");
	d1.c=getch();
	printf("%c",d1.c);

    //data 2
    	printf("\n\n\n\n ");
	printf("******* DATA 2 *******");
	printf("\n Enter Integer Value for 'i' of 'struct MyData d2' : ");
	scanf("%d",&d2.i);

	printf("\n\n Enter Float Value for 'f' of 'struct MyData d2' : ");
	scanf("%f",&d2.f);

	printf("\n\n Enter Double Value for 'd' of 'struct MyData d2' : ");
	scanf("%lf",&d2.i);

	printf("\n\n Enter Char Value for 'c' of 'struct MyData d2' : ");
	d2.c=getch();
	printf("%c",d2.c);

	//data 3
		printf("\n\n\n\n ");
	printf("******* DATA 3 *******");
	printf("\n Enter Integer Value for 'i' of 'struct MyData d3' : ");
	scanf("%d",&d3.i);

	printf("\n\n Enter Float Value for 'f' of 'struct MyData d3' : ");
	scanf("%f",&d3.f);

	printf("\n\n Enter Double Value for 'd' of 'struct MyData d3' : ");
	scanf("%lf",&d3.i);

	printf("\n\n Enter Char Value for 'c' of 'struct MyData d3' : ");
	d3.c=getch();
	printf("%c",d3.c);
	
	answer_data = AddStructMembers(d1, d2, d3);

    printf("\n\n\n\n ");
	printf("********** ANSWER *********\n\n");
	printf("\n answer_data.i = %d\n", answer_data.i);
	printf("\n answer_data.f = %f\n", answer_data.f);
	printf("\n answer_data.d = %lf\n", answer_data.d);

	answer_data.c = d1.c;
	printf("\n answer_data.c (from data1) = %c\n\n", answer_data.c);

	answer_data.c = d2.c;
	printf("answer_data.c (from data2) = %c\n\n", answer_data.c);

	answer_data.c = d3.c;
	printf("answer_data.c (from data3) = %c\n\n", answer_data.c);

	return(0);

		
}

struct MyData AddStructMembers(struct MyData md_one,struct MyData md_two,struct MyData md_three)
{
	struct MyData answer;

	answer.i = md_one.i + md_two.i + md_three.i;
	answer.f = md_one.f + md_two.f + md_three.f;
	answer.d = md_one.d + md_two.d + md_three.d;

	return(answer);
}
