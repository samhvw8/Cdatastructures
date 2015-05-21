

/* Author : Hoang Van Sam
 * ICT58 - HUST
 * -Single linklist-v3
 * Update date : 06/05/2015
 * Change type to void *
 */

#include "link.h"


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


void linit(llist *l){

  l->r = NULL;


  l->l = NULL;


  l->c = NULL;
}


//make node
node *makeNode(void * val){
  node *p;
  p  = (node *)malloc(sizeof(node));
  p->next = NULL;
  p->v = val;
  return p;
}

// find pev node of node p
node *prevNode(llist *l,node *p){
  if(l->r == NULL) return NULL;
  node *z =  l->r;
   if (z == p) return z;
  else {
    while(z != NULL){
      if(z->next == p) return z;
      z = z->next;
    }
    return NULL;
  }
}
// insert begin of list
void insertB(llist *l,void * val){
  node *p;
  p = makeNode(val);

  if(l->r == NULL) {
    /* printf("1"); */
    l->r = p;
    l->l = p;
    l->c = p;
  } else {
    /* printf("0"); */
    p->next =l->r;
    l->r =p;
    l->c = p;
  }
}

// insert node to end

void insertE(llist *l,void * val){
  node *p;
  p = makeNode(val);

  if(l->r == NULL) {
    l->r = p;
    l->l = p;
    l->c = p;
  } else {
    //node *last = *list->l;
    (l->l)->next = p;
    l->l = p;
    l->c = p;
  }
}


// del node p
void delNode(llist *l,node *p){

  node *pev = prevNode(l,p);
  l->c = pev;
  if(p == l->r){
    l->r = p->next;
  } else {
    pev->next = p->next;
    if(p == l->l){
      l->l = pev;
    }
  }
  free(p);
}


// insert node before node p
void insertNb(llist *l,node *p,void * val){
  node *q = makeNode(val);
  l->c = q;
   if(l->r == NULL) {
    printf("Node haven't create !!");
    return;
  } else if(l->r == p) {
     l->r = q;
      q->next = p;
   } else {
      q->next = p;
      prevNode(l,p)->next = q;
  }
}


// insert node after node p
void insertNa(llist *l,node *p,void * val){
  node *q = makeNode(val);
  l->c = q;
  if(l->r == NULL) {
    return;
  } else {
    if(l->l == p) {
      insertE(l,val);
      free(q);
    }  else  {
      q->next = p->next;
      p->next =q;
    }
  }
}


// reverse list
void reversel(llist *l){
  node *z,*p;
  l->l = l->r;


  p = l->r;

  l->r = l->r->next;

  z = l->r;
  l->r = l->r->next;
  z->next =p;


  while (l->r != NULL) {
    p = z;
    z = l->r;
    l->r =l->r->next;
    z->next =p ;
 }

  l->r = z;
  l->l->next = NULL;
  l->c = l->r;
}

//count List
int countList(llist l){
  node *p = l.r;
  int c = 0;
  while (p != NULL) {
    c++;
    p = p ->next;
  }
  return c;
}

// insert at position

node *insertAtPosition(llist *l,void * v,int n){
  if(l->r == NULL ) {
    printf("\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(*l) -1) {
    printf("\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    insertB(l,v);
  } else if(n == countList(*l)){
    insertNb(l,l->l,v);
  } else {
    int c = 0;
    node *p = l->r->next;
    while (p != NULL) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    insertNb(l,p,v);
  }
  return l->c;
}

// delete at position

node *deleteAtPosition(llist *l,int n){
  if(l->r == NULL ) {
    printf("\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(*l) -1) {
    printf("\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    delNode(l,l->r);
  } else if(n == countList(*l)){
    delNode(l,l->l);
  } else {
    int c = 0;
    node *p = l->r->next;
    while (p != NULL) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    delNode(l,p);
  }
  return l->c;
}

// Devide list

llist *devideList(llist *l,int p){
  if(l->r == NULL) {
    printf("Haven't list insert !!\n");
    return NULL;
  }
  if(p < 0 ||  p > countList(*l) -1){
    printf("Positon value invaild !!\n");
    return NULL;
  }

  llist *ln;
  ln = (llist *)malloc(sizeof(llist));
  linit(ln);


  int c = 0;
  node *z = l->r->next;
  while (z != NULL) {
    c++;
    if(c == p) break;
    z = z ->next;
  }

  ln->r = z->next;
  ln->l = l->l;

  l->l = z;

  z->next = NULL;

  l -> c = l -> l;
  ln->c = ln->l;

  return ln;
}

// Extract list

void extractList(llist *l,int p,int n){
  if(l->r == NULL) {
    printf("Haven't list insert !!\n");
    return ;
  }
  if(p < 0 ||  p > countList(*l) -1){
    printf("Positon value invaild !!\n");
    return ;
  }
  if(n < 0 ||p+ n-1 > countList(*l) -1){
    printf("number value invaild !!\n");
    return ;

  }
  node *r = l->r;
  node *rn = l->r;
  node *ln = l->l;
  int c = 0;
  node *z = l->r->next;
  while (z != NULL) {
    c++;
    if(c == p) rn =z;
    if(c == p+n-1) {ln =z;break;}
    z = z ->next;
  }
  l->r = rn;
  l->l = ln;
  if(p != 0){
    prevNode(l,l->r)->next = NULL;
    freelist(l->r);
  }
  freelist(z->next);
  ln ->next =NULL;
  l->c = l->l;
}



// merge list

void mergelist(llist *l,llist *l2){
  l->l->next = l2->r;
  l2->r ==  NULL;

  l->l = l2 -> l;
  l->c = l->l;
  l2 -> l = NULL;
  l2 -> c = NULL;

}
