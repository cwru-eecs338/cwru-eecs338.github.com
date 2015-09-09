#include <stdio.h>

int main()
{
	int numbers[5] = { 0, 1, 2, 3, 4 };
	int i;

	for (i = 0; i < 500000; i++) {
		printf("%i\n", numbers[i]);
	}
}
