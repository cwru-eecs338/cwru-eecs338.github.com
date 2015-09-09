#include <stdio.h>
#include <stdlib.h>

void double_array(int number_array[], int array_size);

int main()
{
	int * pointer_to_array;             // since arrays and pointers used as arrays behave the same,
                                        // "pointer_to" is a little redundant
	int   number_of_ints_to_allocate;
	int   i;                            // double checked on the eecslinab3 machine, you need to declare
                                        // declare this outside of the for loop

	printf("how many elements do you want in your array? ");
	scanf("%i", &number_of_ints_to_allocate);

    // malloc takes THE NUMBER OF BYTES to allocate on the HEAP

	pointer_to_array = malloc(sizeof(int) * number_of_ints_to_allocate);

    // what if we wanted to only allocate a single int?
    // just take away "* number_of_ints_to_allocate"

	for (i = 0; i < number_of_ints_to_allocate; i++) {
		scanf("%i", &pointer_to_array[i]);
	}

    // don't need &pointer_to_array or *pointer_to_array...
    // remember that arrays are the same as pointers when passed across functions
	double_array(pointer_to_array, number_of_ints_to_allocate);

	printf("doubled array: ");
	for (i = 0; i < number_of_ints_to_allocate; i++) {
		printf("%i ", pointer_to_array[i]);
	}
	pritnf("\n");

    // C has no garbage collector, you MUST say that you're done with memory
    // so that you don't run out later or use too much by accident.
    // EVERY malloc SHOULD BE PAIRED WITH A free.

	free(pointer_to_array);

    // and what would happen if we tried to use the array still?
    // ex: pointer_to_array[3]
}

// "int * number_array" would also be correct
void double_array(int number_array[], int array_size)
{
	int i;

	for (i = 0; i < array_size; i++) {
		number_array[i] *= 2;
	}
}

