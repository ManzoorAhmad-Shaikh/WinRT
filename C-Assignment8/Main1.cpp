#include <stdio.h>

int main()
{
    int i=0,j=0,n=0;
    printf("Enter the length of triangle\n");
    scanf("%d",&n);
    printf("\n");
    for(i=1;i<=n;i++){
        for(j=1;j<=i;j++){
            printf("*");
        }
        printf("\n");
    }

    return 0;
}