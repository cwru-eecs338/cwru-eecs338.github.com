#include <stdio.h>

int power(int x, int y);

// what if we wanted to write this after main...?

int main()
{
	int result;

	result = power(3, 4);
	printf("3 to the 4th power is %i %i.\n", result, result);
}

int power(int x, int y)
{
	int i;
	int result = 1;

	for (i = 0; i < y; i++) {
		result *= x;
	}

	return result;
}
