#include<stdio.h>
#include<stdlib.h>
 
/* Link list node */
struct node
{
    int data;
    struct node* next;
};
 
/* Function to remove loop. Used by detectAndRemoveLoop() */
void removeLoop(struct node *, struct node *);
 
/* This function detects and removes loop in the list
  If loop was there in the list then it returns 1,
  otherwise returns 0 */
int detectAndRemoveLoop(struct node *list)
{
    struct node  *slow_p = list, *fast_p = list;
 
    while (slow_p && fast_p && fast_p->next)
    {
        slow_p = slow_p->next;
        fast_p  = fast_p->next->next;
 
        /* If slow_p and fast_p meet at some point then there
           is a loop */
        if (slow_p == fast_p)
        {
		printf("slow_p = %d", slow_p->data);
            removeLoop(slow_p, list);
 
            /* Return 1 to indicate that loop is found */
            return 1;
        }
    }
 
    /* Return 0 to indeciate that ther is no loop*/
    return 0;
}
 
/* Function to remove loop.
 loop_node --> Pointer to one of the loop nodes
 head -->  Pointer to the start node of the linked list */
void removeLoop(struct node *loop_node, struct node *head)
{
   struct node *ptr1;
   struct node *ptr2; 
   struct node *temp; 
   /* Set a pointer to the beging of the Linked List and
      move it one by one to find the first node which is
      part of the Linked List */
   ptr1 = head;
   while (1)
   {
     /* Now start a pointer from loop_node and check if it ever
       reaches ptr2 */
     ptr2 = loop_node;
     while (ptr2 != loop_node)
         ptr2 = ptr2->next;
     printf("ptr2 = %d", ptr2->data); 
     /* If ptr2 reahced ptr1 then there is a loop. So break the
        loop */
     
     ptr2->next = NULL;
     break;
   }
}
 
/* Function to print linked list */
void printList(struct node *node)
{
    while (node != NULL)
    {
        printf("%d  ", node->data);
        node = node->next;
    }
}

void push(struct node **head_ref, int new_data)
{
	struct node* new_node = (struct node*) malloc(sizeof(struct node));
	
	new_node->data = new_data;
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}
 
/* Drier program to test above function*/
int main()
{
    struct node *head = NULL;
    push(&head, 5);
    push(&head,	4);
    push(&head, 3);
    push(&head, 2);
    push(&head, 1);

    printList(head);

    printf("data = %d\n", head->data);
	struct node* temp;
    temp = head->next;
    printf("temp = %d", temp->data);
//    temp = head->next->next->next->next->next;    /* Create a loop for testing */
//    printf("temp - %d", temp->data);
	head->next->next->next->next->next = head->next;
 
    detectAndRemoveLoop(head);
 
    printf("Linked List after removing loop \n");
    printList(head);
    return 0;
}
