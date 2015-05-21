
#ifndef _DLINK_H_GIN_
#define _DLINK_H_GIN_



typedef int ETYPE;

#include <stdio.h>
#include <stdlib.h>
typedef struct node node;
struct node {
  ETYPE v;
  node *next;
  node *prev;
};

typedef struct $llist {
  node *r;
  node *l;
  node *c;
} llist;

// free list
void freelist(node *r);
void delNodeR(llist *l);

void linit(llist *l);

// make node
node *makeNode(ETYPE val);

// insert end of list
void insertE(llist *l,ETYPE val);
// insert node before
void insertNb(llist *l,node *p,ETYPE val);
//insert node after
void insertNa(llist *l,node *p,ETYPE val);


// del node
void delNode(llist *l,node *p);


// reverse list
void reversel(llist *l);
//count dual node List
int countList(node *r);


// insert begin of list
void insertB(llist *l,ETYPE val);
// insert at position

node *insertAtPosition(llist *l,ETYPE v,int n);
// delete at position

node *deleteAtPosition(llist *l,int n);

// Devide list

llist *devideList(llist *l,int p);
// Extract list

void extractList(llist *l,int p,int p2);


void mergelist(llist *l,llist *l2);

#endif
