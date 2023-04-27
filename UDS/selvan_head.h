#ifndef SELVAN_HEAD_H
#define SELVAN_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

//Node Structure of the Linked List
typedef struct Node {
    int data;
    struct Node* next;
} Node;

#define MAX_LIMIT 100 //maximum no of nodes allowed in the LL

extern int no_of_nodes;
extern int ins_flag;
extern int del_flag;



// create node - helper function
struct Node *createNode(int val);

//-------------------------------//
// THE-INSERTING-FUNCTION BELOW //
//-------------------------------//

struct Node *insert(struct Node *head, int val, int pos);

//-------------------------------//
//   THE-DELETE-NODE-FUNCTIONS   //
//-------------------------------//

struct Node *delete(struct Node *head, int pos);

//-------------------------------//
//   THE-NODE-FINDING-FUNCTIONS  //
//-------------------------------//
struct Node *findValueAtPosition(struct Node *head, int value);

//-------------------------------//
//  THE-LL -DISPLAYING-FUNCTIONS //
//-------------------------------//

void display(struct Node *head);

#endif

