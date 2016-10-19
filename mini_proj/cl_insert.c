#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
};

void insert_sort(struct node** head, int new_data)
{
	struct node* new_node = (struct node*) malloc (sizeof(struct node));
	struct node* temp = *head;
	struct node* prev = NULL;
	struct node* next = NULL;
	new_node->data = new_data;
	new_node->next = *head;

	if (head != NULL) {
					if (new_node->data >= (*head)->data) {
							while (temp->next != *head)
								temp = temp->next;
							temp->next = new_node;
							new_node->next = *head;
							*head = new_node;
					} else {
						while (temp->next != *head && new_node->data <= temp->data) {
								next = temp->next;
								prev = temp;
								temp = next;
								printf("prev = %d\n", temp->data);
						}
						if (new_node->data  >= temp->data) {
							prev->next = new_node;
							new_node->next = temp;
							
						} else {
							printf("kfjgkl\n");
							temp->next = new_node;
							new_node->next = (*head);

						}
					}
	}
}

void push(struct node** head_ref, int new_data)
{
	struct node* new_node = NULL;
	struct node* temp = *head_ref;
	new_node = (struct node*) malloc (sizeof(struct node));
	
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

void print_list (struct node* head)
{
	struct node* temp = head;
	do {
		printf("%d->", temp->data);
		temp = temp->next;
	} while (temp != head);
}

int main()
{
	struct node* head = NULL;
	
	push(&head, 5);
	push(&head, 6);
	push(&head, 7);
	push(&head, 10);
	push(&head, 12);
	insert_sort(&head, 0);
	print_list(head);
	return 0;
}	
