#include <stdio.h>

int square(int x)
{
	return x * x;
}

int main()
{
	int number_to_square;
	int scanf_results;

	printf("Enter number to square: ");
	scanf_results = scanf("%i", &number_to_square);

	if (scanf_results != 1) {
		printf("Error!\n");
		return 1;
	}

	printf("%i squared is %i.\n", 
			number_to_square, 
			square(number_to_square));

	return 0;
}

