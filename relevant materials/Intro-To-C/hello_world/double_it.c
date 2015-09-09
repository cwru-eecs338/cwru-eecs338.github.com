#include <stdio.h>

int main()
{
	int	my_number;
	int	scanf_results;

	printf("Please enter a number: ");
	scanf_results = scanf("%i", &my_number);

	if (scanf_results != 1) {
		printf("Error: PEBKAC.\n");
		return 1;
	}

	my_number *= 2;
	printf("Result: %i\n", my_number);

	return 0;
}

