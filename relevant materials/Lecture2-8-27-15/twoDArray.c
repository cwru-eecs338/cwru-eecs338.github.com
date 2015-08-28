#include <stdio.h>
#include <stdlib.h>
//shows how you can make 2D arrays.
void main(void) {
	char too_d_arr[200][400]; //create the array on the stack
	char **two_d_arr;//Here, we want to make the array on the heap, so first declare pointer to a pointer 
				 	 //The goal is to make an array of pointers. (AKA array of arrays)
	two_d_arr = malloc(200 * sizeof(char *)); //Allocate space for an array of 200 char pointers.
	two_d_arr[0] = malloc(400 * sizeof(char)); //For the first array of arrays, allocate space for 400 chars
	two_d_arr[0][13] = 'A'; //set the 13th element of the first array in the array of arrays to 'A'
	two_d_arr[3][13] = 'B'; //This line will cause segfault. Because the 3rd array never had space allocated for it, only the first one did
	printf("Position 0, 13: %c\n", two_d_arr[0][13]);	
	/*printf("Position 3, 13: %c\n", two_d_arr[3][13]);*/
}
