#include<stdio.h>
#include<stdlib.h>


/* Author : Hoang Van Sam
 * ICT58 - HUST
 * -Single linklist-
 */

typedef int VARTYPE;
typedef struct node node;
typedef struct node {
  VARTYPE element;
  node* next;
}node;

node * root = NULL;
node * last = NULL;


//make node
node *makeNode(VARTYPE val){
  node *p;
  p  = (node *)malloc(sizeof(node));
  p->next = NULL;
  p->element = val;
  return p;
}


// insertnode to end

void insertN(VARTYPE val){
  node *p;
  p = makeNode(val);

  if(root == NULL) {
    root = p;
    last = p;
  } else {
    last->next = p;
    last = p;
  }
}


// find node
node *findNode(VARTYPE val){
  node *p = root;
  if (root == NULL) return NULL;
  else {
    while(p != NULL){
      if(p->element == val) return p;
      else p= p->next ;
    }
    printf("Not found \n");
    return NULL;
  }
}


// find pev node of node p
node *pevNode(node *p){
  node *z = root;
  if(root == NULL) return NULL;
  else if (z == p) return z;
  else {
    while(z != NULL){
      if(z->next == p) return z;
      z = z->next;
    }
    return NULL;
  }
}


// del node p
void delNode(node *p){

  node *pev = pevNode(p);
  if(p == root){
    root = p->next;
  } else {
    pev->next = p->next;
    if(p == last){
      last = pev;
    }
  }
  free(p);
}



// insert node before node p
void insertNb(node *p,VARTYPE val){
  node *q = makeNode(val);
   if(root == NULL) {
    printf("Node haven't create !!");
    return;
  } else if(root == p) {
      root = q;
      q->next = p;
   } else {
      q->next = p;
      pevNode(p)->next = q;
  }
}


// insert node after node p
void insertNa(node *p,VARTYPE val){
  node *q = makeNode(val);
  if(root == NULL) {
    printf("Node haven't create !!");
    return;
  } else {
    if(last == p) {
      insertN(val);
      free(q);
    }  else  {
      q->next = p->next;
      p->next =q;
    }
  }
}
