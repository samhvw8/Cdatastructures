/*
  Double link lib
  Author Ginz
  Update : 06/05/2015
  Change type to void *
 */


#ifndef _DLINK_H_GIN_
#define _DLINK_H_GIN_

#include <stdio.h>
#include <stdlib.h>
typedef struct node node;
struct node {
  void * v;
  node *next;
  node *prev;
};

typedef struct $llist {
  node *r; // root of list
  node *l; // last of list
  node *c; // currunt on list
} llist;

// free list
void freelist(node *r);
// Del node at root
void delNodeR(llist *l);

// List install
void linit(llist *l);

// make node
node *makeNode(void * val);

// insert end of list
void insertE(llist *l,void * val);
// insert node before
void insertNb(llist *l,node *p,void * val);
//insert node after
void insertNa(llist *l,node *p,void * val);


// del node
void delNode(llist *l,node *p);


// reverse list
void reversel(llist *l);
//count dual node List
int countList(node *r);


// insert begin of list
void insertB(llist *l,void * val);
// insert at position

node *insertAtPosition(llist *l,void * v,int n);
// delete at position

node *deleteAtPosition(llist *l,int n);

// Devide list

llist *devideList(llist *l,int p);
// Extract list

void extractList(llist *l,int p,int p2);


void mergelist(llist *l,llist *l2);

#endif
