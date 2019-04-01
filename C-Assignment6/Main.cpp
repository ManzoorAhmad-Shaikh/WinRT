#include <stdio.h>

void FibonacciOne(int);
void FibonacciTwo(int);
int main()
{
    int n=0;

    printf("Enter the number of terms: ");
    scanf("%d", &n);
	FibonacciOne(n);
	FibonacciTwo(n);
    return 0;
}

void FibonacciOne(int n){
	int i, t1 = 0, t2 = 1, nextTerm;
    printf("\nFibonacci Series: ");

    for (i = 1; i <= n; ++i)
    {
        printf("%d, ", t1);
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }
}

void FibonacciTwo(int n){
	int t1 = 0, t2 = 1, nextTerm = 0;
	// displays the first two terms which is always 0 and 1
    printf("\nFibonacci Series: %d, %d, ", t1, t2);

    nextTerm = t1 + t2;

    while(nextTerm <= n)
    {
        printf("%d, ",nextTerm);
        t1 = t2;
        t2 = nextTerm;
        nextTerm = t1 + t2;
    }
    
}

