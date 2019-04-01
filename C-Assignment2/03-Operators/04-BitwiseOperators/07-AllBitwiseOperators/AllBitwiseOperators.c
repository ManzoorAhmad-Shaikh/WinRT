#include <stdio.h>

int main(void)
{
	//Function prototypes
	void PrintBinaryFormOfNumber(unsigned int);

	//Variable declarations
	unsigned int a;
	unsigned int b;
	unsigned int right_shift_A, right_shift_B;
	unsigned int left_shift_A, left_shift_B;
	unsigned int result;

	//code
	printf("\n\n");
	printf("Enter An Integer = ");
	scanf("%u", &a);

	printf("\n\n");
	printf("Enter Another Integer = ");
	scanf("%u", &b);

	printf("\n\n");
	printf("By How Many Bits Do You Want To Shift A = %d To The Right ? ", a);
	scanf("%u", &right_shift_A);

	printf("\n\n");
	printf("By How Many Bits Do You Want To Shift B = %d To The Right ? ", b);
	scanf("%u", &right_shift_B);

	printf("\n\n");
	printf("By How Many Bits Do You Want To Shift A = %d To The Left ? ", a);
	scanf("%u", &left_shift_A);

	printf("\n\n");
	printf("By How Many Bits Do You Want To Shift B = %d To The Left ? ", b);
	scanf("%u", &left_shift_B);

	printf("\n\n\n\n");
	result = a & b;
	printf("Bitwise AND-ing Of \nA = %d (Decimal), %o (Octal), %X (Hexadecimal) and \nB = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The Result = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", a, a, a, b, b, b, result, result, result);
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = a | b;
	printf("Bitwise OR-ing Of \nA = %d (Decimal), %o (Octal), %X (Hexadecimal) and \nB = %d (Decimal), %o (Octal), %X (Hexadecimal) Gives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", a, a, a, b, b, b, result, result, result);
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = a ^ b;
	printf("Bitwise XOR-ing Of \nA = %d (Decimal), %o (Octal), %X (Hexadecimal) and \nB = %d (Decimal), %o (Octal), %X (Hexadecimal) Gives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", a, a, a, b, b, b, result, result, result);
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = ~a;
	printf("Bitwise COMPLEMENT Of \nA = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", a, a, a, result, result, result);
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = ~b;
	printf("Bitwise COMPLEMENT Of \nB = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", b, b, b, result, result, result);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = a >> right_shift_A;
	printf("Bitwise RIGHT-SHIFT By %d Bits Of \nA = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", right_shift_A, a, a, a, result, result, result);
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = b >> right_shift_B;
	printf("Bitwise RIGHT-SHIFT By %d Bits Of \nB = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", right_shift_B, b, b, b, result, result, result);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = a << left_shift_A;
	printf("Bitwise LEFT-SHIFT By %d Bits Of \nA = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", left_shift_A, a, a, a, result, result, result);
	PrintBinaryFormOfNumber(a);
	PrintBinaryFormOfNumber(result);

	printf("\n\n\n\n");
	result = b << left_shift_B;
	printf("Bitwise LEFT-SHIFT By %d Bits Of \nB = %d (Decimal), %o (Octal), %X (Hexadecimal) \nGives The \nResult = %d (Decimal), %o (Octal), %X (Hexadecimal).\n\n", left_shift_B, b, b, b, result, result, result);
	PrintBinaryFormOfNumber(b);
	PrintBinaryFormOfNumber(result);

	return(0);
}


// ****** BEGINNERS TO C PROGRAMMING LANGUAGE : PLEASE IGNORE THE CODE OF THE FOLLOWING FUNCTION SNIPPET 'PrintBinaryFormOfNumber()' ******
// ****** YOU MAY COME BACK TO THIS CODE AND WILL UNDERSTAND IT MUCH BETTER AFTER YOU HAVE COVERED : ARRAYS, LOOPS AND FUNCTIONS ******
// ****** THE ONLY OBJECTIVE OF WRITING THIS FUNCTION WAS TO OBTAIN THE BINARY REPRESENTATION OF DECIMAL INTEGERS SO THAT BIT-WISE AND-ing, OR-ing, COMPLEMENT AND BIT-SHIFTING COULD BE UNDERSTOOD WITH GREAT EASE ******

void PrintBinaryFormOfNumber(unsigned int decimal_number)
{
	//variable declarations
	unsigned int quotient, remainder;
	unsigned int num;
	unsigned int binary_array[8];
	int i;

	//code
	for (i = 0; i < 8; i++)
		binary_array[i] = 0;

	printf("The Binary Form Of The Decimal Integer %d Is\t=\t", decimal_number);
	num = decimal_number;
	i = 7;
	while (num != 0)
	{
		quotient = num / 2;
		remainder = num % 2;
		binary_array[i] = remainder;
		num = quotient;
		i--;
	}

	for (i = 0; i < 8; i++)
		printf("%u", binary_array[i]);

	printf("\n\n");
}
