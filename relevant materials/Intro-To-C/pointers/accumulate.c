#include <stdio.h>

void accumulate(int * acc, int val);

int main()
{
	int accumulator = 0;

	printf("acc: %i\n", accumulator);

	accumulate(&accumulator, 3);
	printf("acc: %i\n", accumulator);

	accumulate(&accumulator, 5);
	printf("acc: %i\n", accumulator);

	accumulate(&accumulator, 4);
	printf("acc: %i\n", accumulator);
}

void accumulate(int * acc, int val)
{
	*acc += val;
}

