#include "selvan_head.h"

extern int no_of_nodes;
extern int ins_flag;
extern int del_flag;

//-------------------------------//
//      THE-CREATE-FUNCTION      //
//-------------------------------//

struct Node *createNode (int val) {
    if (no_of_nodes >= MAX_LIMIT) {
        printf ("Sorry Dude! Can't create... Maximum Limit Reached!\n");
        ins_flag = 1;
        return NULL;
    }
    struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));
    if (newNode == NULL) {
        printf("Cannot Create New Node !!");
        ins_flag =1;
        return NULL;
    }
    newNode->data = val;
    newNode->next = NULL;
    return newNode;
}

//-------------------------------//
//   THE-INSERTING-FUNCTION      //
//-------------------------------//

struct Node *insert(struct Node *head, int val, int tar_pos) {
    struct Node *temp = head;
    struct Node *newNode = createNode(val);
    if( tar_pos == 0 ) {
        head = newNode;
        head->next = temp;
        no_of_nodes++;
        return head;
    }

    if (tar_pos < -1 || tar_pos > no_of_nodes - 1) {
        printf("Invalid Position.");
        ins_flag = 1;
        return head;
    }

    if (head == NULL) {
        head = newNode;
        no_of_nodes++;
        return head;
    }


    if (tar_pos == -1) {
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
        no_of_nodes++;
        return head;
    }


    int curr_pos = 0;
    while (temp != NULL && curr_pos + 1 != tar_pos) {
        temp = temp->next;
        curr_pos++;
    }

    struct Node *ptr = temp->next;
    temp->next = newNode;
    temp->next->next = ptr;
    free(ptr);
    no_of_nodes++;
    return head;
}



//-------------------------------//
//   THE-DELETE-NODE-FUNCTION    //
//-------------------------------//

struct Node *delete(struct Node *head, int tar_pos) {
    if (head == NULL) {
        printf("Linked list is empty!\n");
        del_flag = 1;
        return head;
    }
    if (tar_pos < -1 || tar_pos >= no_of_nodes) {
        printf("Invalid position!\n");
        del_flag = 1;
        return head;
    }
    struct Node *temp = head;

    //Delete at End
    if( tar_pos == -1 ) {
        while ( temp->next->next != NULL )
            temp = temp->next;
        struct Node *t = temp->next;
        temp->next = NULL;
        free(t);
        return head;
    }
    // Traverse the linked list to find the node to delete
    if (tar_pos == 0) {
        head = head->next;
        free(temp);
        return head;
    }
    int curr_pos = 0;
    while(temp->next != NULL && curr_pos < tar_pos - 1)
    {
        temp = temp->next;
        curr_pos++;
    }
    struct Node *t = temp->next;
    temp->next = t->next;
    free(t);

    no_of_nodes--;
    return head;
}




//-------------------------------//
//   THE-NODE-FINDING-FUNCTIONS  //
//-------------------------------//

//to find the value at a particular pos in the LL
struct Node* findValueAtPosition (struct Node *head, int value) {
    struct Node *temp = head;
	while (temp != NULL && temp->data != value)
		temp = temp->next;	
	if ( temp == NULL ) {

		printf("Data not found");
		return NULL;
	}
	else {
		return temp;	
	}
    return NULL;
}

//-------------------------------//
//  THE-LL -DISPLAYING-FUNCTIONS //
//-------------------------------//

// Function to display the linked list
void display (struct Node *head) {
    if (head == NULL) {
      printf ("Linked list is empty!\n");
      return;
    }
    struct Node *temp = head;
    printf ("The Linked list: ");
    while (temp != NULL) {
      printf ("%d ", temp->data);
      temp = temp->next;
    }
    printf ("\nNo. of Nodes: %d", no_of_nodes);

    printf ("\n");
}


