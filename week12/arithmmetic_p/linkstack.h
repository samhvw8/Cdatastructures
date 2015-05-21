/*
  Author : Ginz
  Link with single linklist
  Update date : 06/05/2015
  Change Change type to void *
*/


#ifndef _LINK_STACK_H_GIN_
#define _LINK_STACK_H_GIN_
#define TOPS(stack) ( stack)->v

typedef struct node node;
typedef struct node {
  void * v;
  node* next;
}node;
#include <stdio.h>
#include <stdlib.h>
typedef node* StackType;

//make node
node *makeNode(void * val);
// del first node p
void dfnode(node **r);
// insert node begin of list
void inodeB(node *p,node **r);
// free list
void freelist(node **r); // free list node
void Sinstall(StackType *stack); // install stack
void Sremove(StackType *s); // remove stack
int empty(StackType stack); // check stack
void push(void * el,StackType *stack); // push to stack
void * pop(StackType *stack); // pop from stack

#endif
