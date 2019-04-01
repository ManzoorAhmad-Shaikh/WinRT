#include <stdio.h>

int main()
{
   int i=0,j=0,n=0,k=0,l=0,m=1;
    printf("Enter the length of triangle\n");
    scanf("%d",&n);
    printf("\n");
    for(i=1,l=n;i<=n,l>=1;i++,l--){
        for(j=1;j<=n;j++){
            if(j<=i)
            printf("%d",j);
            else
            printf(" ");
        }
        for(k=1;k<=n;k++){
            if(k<l)
            printf(" ");
            else
            { m=(n-k)+1;printf("%d",m);m--;}
        }
        printf("\n");
    }



    return 0;
}
