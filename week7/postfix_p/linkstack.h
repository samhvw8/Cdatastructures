

#ifndef _LINK_STACK_H_GIN_
#define _LINK_STACK_H_GIN_

typedef void * ETYPE;

typedef struct node node;
typedef struct node {
  ETYPE v;
  node* next;
}node;
#include <stdio.h>
#include <stdlib.h>
typedef node* StackType;

//make node
node *makeNode(ETYPE val);
// del first node p
void dfnode(node **r);
// insert node begin of list
void inodeB(node *p,node **r);
// free list
void freelist(node **r); // free list node
void Sinstall(StackType *stack); // install stack
void Sremove(StackType *stack); // remove stack
int empty(StackType stack); // check stack
void push(ETYPE el,StackType *stack); // push to stack
ETYPE pop(StackType *stack); // pop from stack

#endif
