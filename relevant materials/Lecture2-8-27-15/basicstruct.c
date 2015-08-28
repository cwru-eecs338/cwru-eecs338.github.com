#include <stdio.h>
#include <stdlib.h>

//demonstrates basic struct use

//A struct containing an int and a char
struct basic_struct {
	int num;
	char ch;
};

void main(void) {
	struct basic_struct bs = {2, 'p'};//This is the syntax to initialize a struct. Note, this is on the stack
	bs.num = 1; //syntax for accessing elements in a struct. Note that you use . when bs is a struct, not a struct pointer
	bs.ch = 't';
	printf("The num is: %d\n", bs.num);
	printf("The char is: %c\n", bs.ch);
	struct basic_struct *bs1 = malloc(sizeof(struct basic_struct));//Initialize a struct on the heap
	bs1->num = 1;//We use -> when bs1 is a pointer to a struct to access the element num of the struct.
	bs1->ch = 's';	
	printf("The num is: %d\n", bs1->num);
	printf("The char is: %c\n", bs1->ch);



}	
