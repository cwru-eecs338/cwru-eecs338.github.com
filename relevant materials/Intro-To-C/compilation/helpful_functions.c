#include "helpful_functions.h"

void double_array(int * num_array, int size)
{
	int i;

	for (i = 0; i < size; i++) {
		num_array[i] *= 2;
	}
}

void accumulate(int * acc, int val)
{
	*acc += val;
}

int square(int x)
{
	return x * x;
}

int power(int x, int y)
{
	int i;
	int result;

	result = 1;

	for (i = 0; i < y; i++) {
		result *= x;
	}

	return result;
}
