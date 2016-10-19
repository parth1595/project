#include <stdio.h>
#include <stdlib.h>

#define ALLOC_FAIL 	0x00
#define SUCCESS 	0x01

struct node
{
	int data;
	struct node* next;
};

static void push(struct node** head_ref, int new_data)
{
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	if (new_node == NULL) {
		printf("\nAllocation Failed\n");
	}
	struct node* temp = *head_ref;
	new_node->data = new_data;
	new_node->next = *head_ref;

	if (*head_ref != NULL) {
		while (temp->next != *head_ref)
			temp = temp->next;
		temp->next = new_node;
	} else
	  	new_node->next = new_node;
	*head_ref = new_node;
}

void print_list (struct node* head_ref)
{
	struct node* temp = head_ref;
	do  {
		printf("%d->",temp->data);
		temp = temp->next;
	} while (temp != head_ref);
}

int main()
{

	struct node* head = NULL;

	push(&head, 5);
	push(&head, 6);
	push(&head, 7);
	push(&head, 8);

	print_list(head);

	return 0;

}	

	

