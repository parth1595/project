#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node* next;
};

void split_list (struct node* head_ref, struct node** list1, struct node** list2, int len)
{
	struct node* temp = head_ref;
	struct node* temp2 = head_ref;
	int end = len;

	int l1_end = (len / 2);
	printf("l1_end = %d\n", l1_end);
	*list1 = temp2;
	if ( len % 2 == 0) {
		while ( len != (l1_end + 1)) {
		printf("list1\n");
		printf("%d->",temp2->data);
		temp2 = temp2->next;
		len--;
		}
		temp = temp2->next;
		printf("ddata=%d\n", temp->data);
		temp2->next = (*list1);
		temp2 = temp2->next;
		printf ("\ntemp2 = %d\n", temp2->data);
		printf("jdghfdgk\n");
		*list2 = temp;
			while (temp->next != temp2) {
				printf ("list 2\n");
				printf("%d->\n", temp->data);
				temp = temp->next;
			}
			temp->next = (*list2);
		printf("final = %d\n", (*list2)->data);
		

//		*list = temp2;
	
//		while ( len != 0) {
//		printf("\n");
//		printf("list2\n");
//		printf("%d->"temp2->
	}
}			

	

void push( struct node** head_ref, int new_data)
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

int detect_loop (struct node *head)
{
	struct node *slow = head;
	struct node *fast = head;
	int count = 0;
	if (head == NULL)
		return;

	printf("fast = %d\n",fast->data);
	printf("slow = %d\n",slow->data);
	while (slow && fast && fast->next) {
		count++;
		slow = slow->next;
		fast = fast->next->next;
		printf("slow = %d\n",slow->data);
		printf("fast = %d\n",fast->data);
		printf("count = %d\n", count);

		if (slow == fast) {
			printf("Loop detected\n");
			return count;
		}
	}

		return count;
}

void print_list (struct node *head)
{
	struct node* temp = head;
	if (head != NULL)
		do {
			printf("->%d", temp->data);
			temp = temp->next;
		} while (temp != head);
}


int main()
{
	struct node* head = NULL;
	struct node* list1 = NULL;
	struct node* list2 = NULL;

	int length = 0;

	push (&head, 5);
	push (&head, 6);
	push (&head, 7);
	push (&head, 8);
	push (&head, 9);
	push (&head, 10);
	print_list(head);
	length = detect_loop(head);
	printf("length = %d", length);
	split_list(head, &list1, &list2, length);
	printf("\n");
	printf("--------lsit1-----------\n");
	print_list(list1);
	printf("-----------lsit2--------\n");
	print_list(list2);
	return 0;
}			
