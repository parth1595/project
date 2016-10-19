#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
};

void swap_nodes(struct node** head_ref, int x, int y)
{
	if (x == y) return;

	struct node *prevX = NULL, *currX = *head_ref;
	while ( currX && currX->data != x) {
		prevX = currX;
		currX = currX->next;
	}
	struct node *prevY = NULL, *currY = *head_ref;
	while ( currY && currY->data != y) {
		prevY = currY;
		currY = currY->next;
	}

	if (currX == NULL || currY == NULL)
		return;
	if (prevX != NULL)
		prevX->next = currY;
	else
		*head_ref = currY;
	if (prevY != NULL)
		prevY->next = currX;
	else
		*head_ref = currX;

	struct node *temp = currY->next;
	currY->next = currX->next;
	currX->next = temp;
}

	

void push(struct node** head_ref, int new_data)
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}


void print_list(struct node *node)
{
	while (node != NULL) {
		printf("%d->", node->data);
		node = node->next;
	}
}

int main() 
{
	struct node *start = NULL;

	push(&start, 7);
	push(&start, 5);
	push(&start, 6);
	push(&start, 4);
	push(&start, 3);
	push(&start, 2);

	printf("\n Linked List before calling swapnodes");
	print_list(start);

	swap_nodes(&start, 4, 3);

	printf("\nLinked list after calling swapnodes ");
	print_list(start);

	return 0;
}
