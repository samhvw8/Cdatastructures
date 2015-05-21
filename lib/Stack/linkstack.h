/*
  Author : Ginz
  Link with single linklist
  Update date : 06/05/2015
  Change Change type to void *
*/


#ifndef _LINK_STACK_H_GIN_
#define _LINK_STACK_H_GIN_


typedef struct node node;
typedef struct nodestack {
  void * v;
  nodes* next;
}nodes;
#define TOP(stack) stack->v
#include <stdio.h>
#include <stdlib.h>

typedef nodes* stack;
typedef stack* stackp;


//make nodes
nodes *makeNode(void * val);
// del first nodes p
void dfnode(nodes **r);
// insert nodes begin of list
void inodeB(nodes *p,nodes **r);


// free list
void freelist(nodes **r); // free list nodes
void Sinstall(stackp stack); // install stack
void Sremove(stackp stack); // remove stack
int empty(stack stack); // check stack
void push(void * el,stackp stack); // push to stack
void *pop(stackp stack); // pop from stack

#endif
