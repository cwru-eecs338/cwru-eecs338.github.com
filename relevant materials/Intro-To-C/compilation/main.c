#include <stdio.h>
#include "helpful_functions.h"

int main()
{
	int numbers[5] = { 1, 2, 3, 4, 5 };
	int i;
	int acc;

	double_array(numbers, 5);
	printf("some numbers that have been doubled: ");
	for (i = 0; i < 5; i++) {
		printf("%i ", numbers[i]);
	}
	printf("\n");

	printf("2 squared: %i.\n", square(2));
	printf("3 to the 5th power: %i\n", power(3, 5));

	acc = 0;
	printf("acc: %i\n", acc);
	accumulate(&acc, 3);
	printf("acc: %i\n", acc);
	accumulate(&acc, 7);
	printf("acc: %i\n", acc);
}
