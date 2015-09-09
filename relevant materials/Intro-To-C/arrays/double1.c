#include <stdio.h>

int main()
{
	int some_numbers[5];
	int i;

	printf("Enter five numbers: ");

	// read five numbers

	for (i = 0; i < 5; i++) {
		scanf("%i", &some_numbers[i]);
	}

	// double everything in the array

	for (i = 0; i < 5; i++) {
		some_numbers[i] *= 2;
	}

	// print it all back out
	printf("The array: [");
	for (i = 0; i < 5; i++) {
		printf("%i, ", some_numbers[i]);
	}
	printf("]\n");
}

