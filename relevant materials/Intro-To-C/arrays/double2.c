#include <stdio.h>

void double_array(int array[], int array_size);

int main()
{
	int nums[5] = { 1, 2, 3, 4, 5 };
	int i;

	double_array(nums, 5);

	for (i = 0; i < 5; i++) {
		printf("%i\n", nums[i]);
	}
}

void double_array(int array[], int array_size)
{
	int i;

	for (i = 0; i < array_size; i++) {
		array[i] *= 2;
	}
}
