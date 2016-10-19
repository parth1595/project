#include <stdio.h>
#include <stdlib.h>

struct node 
{
	int data;
	struct node* prev;
	struct node* next;
};

void delete_node (struct node* ref_node)
{
	struct node* temp = NULL;
	temp = ref_node->prev;	
	temp->next = ref_node->next;
	temp->next->prev = temp;
}

void insert_after (struct node* ref_node, int new_data)
{
	struct node* new_node = NULL;

	new_node = (struct node *) malloc (sizeof(struct node));

	new_node->data = new_data;
	if (ref_node->next == NULL) {
		ref_node->next = new_node;
		new_node->prev = ref_node;
		new_node->next = NULL;
	} else {
	new_node->next = ref_node->next;
	ref_node->next = new_node;
	new_node->next->prev = new_node;
	new_node->prev = ref_node;
	}
}


void push (struct node** head_ref, int new_data)
{
	struct node* new_node = NULL;

	new_node = (struct node*) malloc (sizeof(struct node));

	new_node->data = new_data;
	new_node->next = (*head_ref);

	if (*head_ref != NULL) {
		(*head_ref)->prev = new_node;
	}
	*head_ref = new_node;
}

void print_list(struct node* head)
{
	struct node* temp = NULL;
	while (head != NULL) {
		printf("<-%d->", head->data);
		head = head->next;
	}
}

int main()
{
	struct node* head = NULL;

	push(&head, 5);
	push(&head, 6);
	push(&head, 7);
	push(&head, 9);
	push(&head, 10);

	print_list(head);
	printf("\ndata = %d",(head->next->next)->prev->data);
	insert_after(head, 2);
	printf("\n");
	print_list(head);
	printf("\n data = %d\n",head->next->prev->data);
	delete_node(head->next);
	printf("\n");
	print_list(head);
	return 0;
}
