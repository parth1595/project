#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
};

struct node* new_node(int new_data)
{
	struct node* temp = NULL;
	temp = (struct node*) malloc (sizeof(struct node));
	temp->data = new_data;
	printf("temp= %d",temp->data);
	temp->next = NULL;
	return temp;
}

struct node* sum(struct node* a, struct node* b)
{
	int carry = 0;
	int sum = 0;
	struct node* temp = NULL;
	struct node* result = NULL;
	struct node* prev = NULL;

	while (a != NULL || b != NULL) {
		sum  = (a ? a->data : 0) + (b ? b->data : 0) + carry;
		if(sum > 10) {
			sum = sum % 10;
			carry = 1;
		} else if (sum == 10) {
			sum = sum % 10;
			carry = 1;
		} else {
			carry = 0;
		}
		printf("jngfkf\n");		
		temp = new_node(sum);
		if (result == NULL) {
			result = temp;
			prev = temp;
		} else {
			prev->next = temp;
			prev = prev->next;
		}
		
		if (a != NULL)
			a = a->next;
		if (b != NULL)
			b = b->next;
		printf("sum = %d",temp->data);
	}
	if (carry > 0)
	temp->next = new_node(carry);
		
	return result;
}
static void reverse(struct node** head_ref)
{
	struct node* prev = NULL;
	struct node* current = *head_ref;
	struct node* next = NULL;

	while(current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
} 
		
void push(struct node** head_ref, int data)
{

	struct node* new_node;

	new_node = (struct node *) malloc(sizeof(struct node));

	new_node->data = data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void print_list( struct node* head)
{
	while(head != NULL) {
		printf("%d->",head->data);
		head = head->next;
	}
}

int main()
{
	struct node* a_head = NULL;
	struct node* b_head = NULL;
	struct node* result = NULL;
	push(&a_head, 5);
	push(&a_head, 6);
	push(&a_head, 7);

	push(&b_head, 3);
	push(&b_head, 4);
	push(&b_head, 5);
	print_list(a_head);
	reverse(&a_head);
	printf("\n");
	print_list(a_head);
	printf("\n");
	print_list(b_head);
	reverse(&b_head);
	printf("\n");	
	print_list(b_head);
	printf("\n");
	result = sum(a_head,b_head);
	printf("\n");
	print_list(result);
	return 0;
}

