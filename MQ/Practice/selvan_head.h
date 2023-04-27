#ifndef SELVAN_HEAD_H
#define SELVAN_HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>

#define QUEUE_PERMISSIONS 0660
#define MAX_MSG_SIZE 256
#define MSG_BUFFER_SIZE (MAX_MSG_SIZE + 10)
#define MAX_LIMIT 100 //maximum no of nodes allowed in the LL
#define MAX_MESSAGES 4096

//Node Structure of the Linked List
// struct Node {
//     int data;
//     struct Node *next;
// };
extern int no_of_nodes;
extern int ins_flag;
extern int del_flag;

//Node Structure of the Linked List
// struct Node {
//     int data;
//     struct Node *next;
// };

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

