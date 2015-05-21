#include<stdio.h>
#include<stdlib.h>


/* Author : Hoang Van Sam
 * ICT58 - HUST
 * -Single linklist-
 */

//typedef int VARTYPE;
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
  node *p = NULL;
  p  = (node *)malloc(sizeof(node));
  if(p != NULL){
    p->next = NULL;
    p->element = val;
    return p;
  } else return NULL;
}
// find pev node of node p
node *pevNode(node *r,node *p){
  node *z = r;
  if(r == NULL) return NULL;
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
  z = pevNode(root,last);
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


// del node p
void delNode(node *p){

  node *pev = pevNode(root,p);
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
      pevNode(root,p)->next = q;
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
 void freelist(node *r){
   if (r == NULL) return;
   node *to_free = r;
   while(to_free != NULL){
     r = r ->next;
     free(to_free);
     to_free = r;
   }
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
  z->next =p ;
 }

 root = z;
 last->next = NULL;
 cur = root;
}
//count List
int countList(node *r){
  node *p = r;
  int c = 0;
  while (p != NULL) {
    c++;
    p = p ->next;
  }
  return c;
}
// insert at position

node *insertAtPosition(VARTYPE v,int n){
  if(root == NULL ) {
    printf("\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(root) -1) {
    printf("\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    insertB(v);
  } else if(n == countList(root)){
    insertBE(v);
  } else {
    int c = 0;
    node *p = root->next;
    while (p != NULL) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    insertNb(p,v);
    return cur;
  }
}

// delete at position

node *deleteAtPosition(int n){
  if(root == NULL ) {
    printf("\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(root) -1) {
    printf("\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    delNode(root);
  } else if(n == countList(root)){
    delNode(last);
  } else {
    int c = 0;
    node *p = root->next;
    while (p != NULL) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    delNode(p);
    return cur;
  }
}
// Devide list

node *devideList(node *r,node *l,int p){
  if(r == NULL) {
    printf("Haven't list insert !!\n");
    return NULL;
  }
  if(p < 0 ||  p > countList(r) -1){
    printf("Positon value invaild !!\n");
    return NULL;
  }
  node *rn = NULL;
  int c = 0;
  node *z = r->next;
  while (z != NULL) {
    c++;
    if(c == p) break;
    z = z ->next;
  }
  rn = z->next;
  l = z;
  z->next = NULL;
  return rn;
}

// Extract list

void extractList(int p,int n){
  if(root == NULL) {
    printf("Haven't list insert !!\n");
    return ;
  }
  if(p < 0 ||  p > countList(root) -1){
    printf("Positon value invaild !!\n");
    return ;
  }
  if(n < 0 ||p+ n-1 > countList(root) -1){
    printf("number value invaild !!\n");
    return ;

  }
  node *r = root;
  node *rn = root;
  node *ln = last;
  int c = 0;
  node *z = root->next;
  while (z != NULL) {
    c++;
    if(c == p) rn =z;
    if(c == p+n-1) {ln =z;break;}
    z = z ->next;
  }
  root = rn;
  last = ln;
  if(p != 0){
    pevNode(r,root)->next = NULL;
    freelist(r);
  }
  freelist(z->next);
  ln ->next =NULL;

}



// merge list

void mergelist(node *lastlist1,node *rootlist2){
  lastlist1->next = rootlist2;
  rootlist2 ==  NULL;
}
