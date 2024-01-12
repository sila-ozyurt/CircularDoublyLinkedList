// a program including fundamental operations of circular doubly linked list
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


struct Node {
	int data;
	struct Node* next;
	struct Node* prev;
};


//function below is to insert to head

//
//void insertToHead(struct Node** tail, int data) {
//	
//	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
//	new->data = data;
//
//	if (*tail == NULL) {
//		*tail=new;
//		new->next = new;
//		new->prev = new;
//		return;
//	}
//	new->next = (*tail)->next;
//	new->prev = *tail;
//	(*tail)->next->prev = new;
//	(*tail)->next = new;
//	
//}


//function below is to insert to last


//void insertToLast(struct Node** tail, int data) {
//	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
//	new->data = data;
//
//	if (*tail == NULL) {
//		*tail = new;
//		new->next = new;
//		new->prev = new;
//		return;
//	}
//
//	new->next = (*tail)->next;
//	new->prev = *tail;
//	(*tail)->next = new;
//	(*tail)->next->prev = new;
//
//}



//function below is to insert both according to the choice
void insert(struct Node** tail, int data, char lastORhead) {
	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
	new->data = data;

	if (*tail == NULL) {
		*tail = new;
		new->next = new;
		new->prev = new;
		return;
	}

	new->next = (*tail)->next;
	new->prev = *tail;
	(*tail)->next->prev = new;
	(*tail)->next = new;

	if (tolower(lastORhead) == 'l') {
		*tail = new;
	}
	else if (tolower(lastORhead) == 'h') return;

}

//function to insert after nth node
void insertAfterNthPosition(struct Node **tail,int data,int n) {

	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp = (*tail)->next;

	struct Node* new = (struct Node*)malloc(sizeof(struct Node));
	new->data = data;

	while (n > 1) {
		temp = temp->next;
		n--;
	}

	new->next = temp->next;
	new->prev = temp;
	temp->next->prev = new;
	temp->next = new;
	
	//if temp=tail, then we need to update tail
	if (temp == *tail) {
		*tail = new;
	}

}

//function to delete the given item from the circular doubly linked list
void delete(struct Node** tail, int nodeToDelete) {

	if ((*tail) == NULL)return;

	struct Node* del = (struct Node*)malloc(sizeof(struct Node));
	del = (*tail)->next;

	do {
		if (del->data == nodeToDelete) {
			del->prev->next = del->next;
			del->next->prev = del->prev;
			if (del == *tail) {
				*tail = (*tail)->prev;
			}
			free(del);
			break;  
		}
		del = del->next;
	} while (del != (*tail)->next);

	
}

//function to reverse the list by reversing its next and prev links
void reverseCircularDoublyLinkedList(struct Node** tail) {
	if (*tail == NULL) return;

	struct Node* curr, * prev;
	curr = (*tail)->next;

	do {
		prev = curr->prev;
		curr->prev = curr->next;
		curr->next = prev;
		curr = curr->prev;
	}//we need to break the loop here or else we cannot get out, but tail node hasn't been reversed
	while (curr != *tail);

	//assign new tail
	*tail = curr->next;
	//it should execute for once again
	prev = curr->prev;
	curr->prev = curr->next;
	curr->next = prev;
	
}


//printing the list using *next
void printListNextItem(struct Node* tail) {
	struct Node* head = (struct Node*)malloc(sizeof(struct Node));

	//equalize the head at the beginning of the list
	head = tail->next;

	do {
		printf("%d\t", head->data);
		head = head->next;
	} while (head != tail->next);

	printf("\n\n");
}


int main() {

	struct Node* tail = NULL;

	
	//add h, to insert the value to head
	//add l to insert the value to last
	insert(&tail, 100,'h');
	insert(&tail, 14, 'h');
	insert(&tail, 140,'l');
	insert(&tail, 130,'l');
	insert(&tail, 120,'h');
	printListNextItem(tail);

	insertAfterNthPosition(&tail, 67, 2);
	printListNextItem(tail);

	insertAfterNthPosition(&tail, 90, 6);
	printListNextItem(tail);

	delete(&tail, 67);
	printListNextItem(tail);

	reverseCircularDoublyLinkedList(&tail);
	printListNextItem(tail);

	

	return 0;
}