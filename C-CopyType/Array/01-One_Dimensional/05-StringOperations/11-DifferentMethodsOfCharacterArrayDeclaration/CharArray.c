#include <stdio.h>

int main(void)
{
	//variable declarations 
	char cArray1[] = { 'A', 'S', 'T', 'R', 'O', 'M', 'E', 'D', 'I', 'C', 'O', 'M', 'P', '\0' };
	char cArray2[9] = { 'W', 'E', 'L', 'C', 'O', 'M', 'E', 'S', '\0' };
	char cArray3[] = { 'Y', 'O', 'U', '\0' };
	char cArray4[] = "To";
	char cArray5[] = "REAL TIME RENDERING BATCH OF 2018-19-20"; 

	char cArray_WithoutNullTerminator[] = { 'H', 'e', 'l', 'l', 'o' };

	//code
	printf("\n\n Size Of cArray1 : %d\n", sizeof(cArray1));
	printf("\n\n Size Of cArray2 : %d\n", sizeof(cArray2));
	printf("\n\n Size Of cArray3 : %d\n", sizeof(cArray3));
	printf("\n\n Size Of cArray4 : %d\n", sizeof(cArray4));
	printf("\n\n Size Of cArray5 : %d\n", sizeof(cArray5));

	printf("\n\n The Strings Are : \n");
	printf("\n\n cArray1 : %s\n", cArray1);
	printf("\n\n cArray2 : %s\n", cArray2);
	printf("\n\n cArray3 : %s\n", cArray3);
	printf("\n\n cArray4 : %s\n", cArray4);
	printf("\n\n hArray5 : %s\n", cArray5);

	printf("\n\n Size Of chArray_WithoutNullTerminator : %d\n", sizeof(cArray_WithoutNullTerminator));
	printf("\n\n cArray_WithoutNullTerminator : %s\n", cArray_WithoutNullTerminator);

	return(0);
}


