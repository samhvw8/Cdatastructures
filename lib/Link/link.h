

#ifndef _LINK_H_GIN_
#define _LINK_H_GIN_
#include<stdio.h>
#include<stdlib.h>


/* Author : Hoang Van Sam
 * ICT58 - HUST
 * -Single linklist-v3
 * Update date : 06/05/2015
 * Change type to void *
 */
typedef struct node node;
struct node {
  void * v;
  node* next;
};

typedef struct $ {
  node *r;
  node *l;
  node *c;
} llist;

// free list
void freelist(node *r);


void linit(llist *l);


//make node
node *makeNode(void * val);

// find pev node of node p
node *prevNode(llist *l,node *p);
// insert begin of list
void insertB(llist *l,void * val);

// insert node to end

void insertE(llist *l,void * val);


// del node p
void delNode(llist *l,node *p);

// insert node before node p
void insertNb(llist *l,node *p,void * val);


// insert node after node p
void insertNa(llist *l,node *p,void * val);

// reverse list
void reversel(llist *l);

//count List
int countList(llist l);
// insert at position

node *insertAtPosition(llist *l,void * v,int n);

// delete at position

node *deleteAtPosition(llist *l,int n);

// Devide list

llist *devideList(llist *l,int p);
// Extract list

void extractList(llist *l,int p,int n);



// merge list

void mergelist(llist *l,llist *l2);


#endif
