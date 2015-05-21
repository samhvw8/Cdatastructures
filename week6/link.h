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
node * cur = NULL;

//make node
node *makeNode(VARTYPE val){
  node *p;
  p  = (node *)malloc(sizeof(node));
  p->next = NULL;
  p->element = val;
  return p;
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
// insert begin of list
void insertB(VARTYPE val){
  node *p;
  p = makeNode(val);

  if(root == NULL) {
    root = p;
    last = p;
    cur = p;
  } else {
    p->next = root;
    root =p;
    cur = p;
  }
}

// insert node to end

void insertE(VARTYPE val){
  node *p;
  p = makeNode(val);

  if(root == NULL) {
    root = p;
    last = p;
    cur = p;
  } else {
    last->next = p;
    last = p;
    cur = p;
  }
}
// insert node to before end

void insertBE(VARTYPE val){
  node *p,*z;
  z = pevNode(last);
  p = makeNode(val);
  cur = p;
  if(root == NULL) {
    root = p;
    last = p;
  } else {
    p->next = last;
    z->next = p;
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





// del node p
void delNode(node *p){

  node *pev = pevNode(p);
  cur = pev;
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
// del node begin
void delNodeB(){
  if(root == NULL) return ;
  node *p = root;
  root = p->next;
  cur = root;
  free(p);
}



// insert node before node p
void insertNb(node *p,VARTYPE val){
  node *q = makeNode(val);
  cur = q;
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
  cur = q;
  if(root == NULL) {
    printf("Node haven't create !!");
    return;
  } else {
    if(last == p) {
      insertE(val);
      free(q);
    }  else  {
      q->next = p->next;
      p->next =q;
    }
  }
}

// free list
 void freelist(){
   if (root == NULL) return;
   node *to_free = root;
   while(to_free != NULL){
     root = root ->next;
     free(to_free);
     to_free = root;
   }
 }
// insert before cur
void insertbc(VARTYPE val){
   insertNb(cur,val);
}

// insert after cur
void insertac(VARTYPE val){
   insertNa(cur,val);
}
// reverse list
void reversel(){
  node *z,*p;
  last = root;


  p = root;

  root = root->next;

  z = root;
  root = root->next;
  z->next =p;


while (root != NULL) {
  p = z;
  z = root;
  root =root->next;
  z->next =p;
 }

 root = z;
 last->next = NULL;
 cur = root;
}



