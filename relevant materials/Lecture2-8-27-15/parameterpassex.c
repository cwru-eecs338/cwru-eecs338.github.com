#include <stdio.h>
#include <stdlib.h>


//Couple examples that illustrate how arguments are passed for ints, arrays and structs.

struct arrayStruct {//Our struct contains an array of ints.
	int arr[3];
};

void foo1(int num) {
	num = num + 1;
}

void foo2(int *numptr) {
	*numptr = *numptr + 1;//dereference and increment by 1 and store
}

void manipArr1(int arr[]) {
	arr[1] = -1;
}

void manipArr2(int *arr) {
	*(arr + 1) = -1; //arr is a pointer that points to first element of array
					 //adding 1 will make it point to 2nd element.
					 //store -1 to the contents at arr+1
}

void main(void) {
	int num = 5;
	foo1(num);//call by value, will expect num to be 5
	printf("Result of foo1: %d\n", num);
	int *numptr = &num;
	foo2(numptr);//call by value, but a copy of the pointer is passed, expect num to be 6
	printf("Result of foo2 with pointer passed: %d\n", num);
	int arr[3];
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 0;
	
	manipArr1(arr);//pass in array, but compiler will reinterpret as pointer to first element of array being passed, thus
	printf("Result of manipArr1: %d\n", arr[1]);//arr[1] will be -1
	manipArr2(arr);//pointer to array is passed, arr[1] will be -1 also. manipArr1 and manipArr2 are equivalent.
	printf("Result of manipArr2: %d\n", arr[1]);

	struct arrayStruct *arrStruct = malloc(sizeof(struct arrayStruct));//create a struct on the heap
	(arrStruct->arr)[0] = 0;
	(arrStruct->arr)[1] = 0;
	(arrStruct->arr)[2] = 0;
	manipArrStruct1(*arrStruct);//here we pass the struct to the function, it is call by value, so a copy of the struct is passed
	printf("Result of manipArrStruct1: %d\n", (arrStruct->arr)[1]);//This value will be unchanged since a copy of struct was passed
	manipArrStruct2(arrStruct);//here, we pass a pointer to the struct, so the value will be -1 now.
	printf("Result of manipArrStruct2: %d\n", (arrStruct->arr)[1]);

	//Note that it did not matter if we passed an array vs pointer, but it did matter when we passed struct vs pointer to struct.
	

}

void manipArrStruct1(struct arrayStruct arrStruct) {
	(arrStruct.arr)[1] = -1;
}

void manipArrStruct2(struct arrayStruct *structptr) {
	(structptr->arr)[1] = -1;
}	


 
