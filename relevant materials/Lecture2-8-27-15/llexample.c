#include <stdio.h>
#include <stdlib.h>

/*Struct representing a linked list node. 
it contains two elements, the element of the list, 
and a pointer to the next node. Structs cannot contain 
structs, only pointers to structs. */
struct LLNode {
	int intElement;
	struct LLNode *next;
};

struct LLNode *addElement(struct LLNode *prevNode, int element) {
	struct LLNode *nextNode = malloc(sizeof(struct LLNode));//allocate memory on the heap for the new node we are creating. Must do this on the heap, otherwise
															//our new node will be destroyed after we exit from this function, and we will not be able to have it
															//for use later.
	nextNode->intElement = element;//set the element of the node
	nextNode->next = NULL;//set the next node pointer to NULL so we mark end of list
	prevNode->next = nextNode;//set the previous node to point to our new node. We have to pass in a pointer to the previous node rather than the node itself. 
							  //If we pass in the value of the node, it will be only a copy and the original previous node will not be connected to our new node
	return nextNode;//return a pointer to our new node so that we can track the new end of the list.
}

void printList(struct LLNode *node) { //Print the list by passing in the pointer to the head of the list.
	struct LLNode *ptr = node;
	while (ptr != NULL) {	
		printf("%d", ptr->intElement); 
		ptr = ptr->next; //Keep iterating through the list by setting ptr to the next node
	}
}

void delete(struct LLNode *head, int index) {
	struct LLNode *ptr = head; //same concept as get element, iterate to the index
	int count = 0;
	struct LLNode *prevptr;
	while(count < index) {
		prevptr = ptr;
		ptr = ptr -> next;
		count++;
	}
	
	if(ptr->next != NULL) {//if its not the end of the list, connect the node before the deleted to the node after the deleted
		prevptr->next = ptr->next;
	}
	else {
		prevptr->next = NULL;//if its end of the list set the next to null
	}
	
	free(ptr);//free up the memory for the deleted node.
}

void main(void) {
	struct LLNode *ptr = malloc(sizeof(struct LLNode)); //allocate the head of the list on the heap
	struct LLNode *head = ptr;//store the head
	ptr->intElement = 0;//initialize it
	ptr->next = NULL;
	ptr = addElement(ptr, 1);//add some new elements to the list, store whatever is returned to track end of lits
	ptr = addElement(ptr, 2);
	ptr = addElement(ptr, 3);
	ptr = addElement(ptr, 4);
	ptr = addElement(ptr, 5);
	ptr = addElement(ptr, 6);
	ptr = addElement(ptr, 7);
	ptr = addElement(ptr, 8);
	printList(head);
	printf("%d\n", getElement(head, 3));
	delete(head, 3);
	printList(head);	
	
}

//Get the element at an index
int getElement(struct LLNode *head, int index) {
	struct LLNode *ptr = head;
	int count = 0;
	while(count < index) {//iterate till we are at the index
		ptr = ptr->next;
		count++;
	}
	return ptr->intElement;//access the element and return it
}



