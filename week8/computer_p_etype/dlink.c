
#include "dlink.h"
// free list
void freelist(node *r){
  if (r == NULL) return;
  node *to_free = r;
  while(to_free != NULL){
    r =  r ->next;
    free(to_free);
    to_free = r;
  }
}


void linit(llist *l){

  l->r = NULL;
  l->l = NULL;
  l->c = NULL;
}


// make node
node *makeNode(ETYPE val){
  node *new = (node *)malloc(sizeof(node));
  new->v = val;
  new->next = NULL;
  new->prev =NULL;
  return new;
}

// insert end of list
void insertE(llist *l,ETYPE val){
  node *p = makeNode(val);

  if(l->r == NULL){
    l->r = p;
    l->l = p;
    l->c  =p;
  } else {
    l->l->next = p;
    p->prev = l->l;
    l->l = p;
    l->c =p;
  }
}
// insert node before
void insertNb(llist *l,node *p,ETYPE val){
  node *q = makeNode(val);

  if(l->r == NULL) {
    insertE(l,val);
    l->c =q;
    free(q);
  } else if(p == l->r){
    l->r = q;
    p->prev = q;
    q->next = p;
    l->c = q;
  }else {
    p->prev->next = q;
    q->prev = p->prev;
    l->c = q;
    p->prev = q;
    q->next = p;
  }
}
//insert node after
void insertNa(llist *l,node *p,ETYPE val){
  node *q = makeNode(val);
  if(l->r ==NULL){
    insertE(l,val);
    free(q);
  } else if(p == l->l){
    l->l =q;
    p->next = q;
    q->prev = p;
    l->c = q;
  } else {
    p->next->prev = q;
    q->next = p->next;
    l->c = q;
    p->next = q;
    q->prev = p;
  }
}
//del root
void delNodeR(llist *l){
  delNode(l,l->r);
}

void delNode(llist *l,node *p){
  if(l->r == NULL) return ;
  if(p == NULL) return ;


  if(p == l->r){
    l->r = p->next;
    if(p != l->l)  p->next->prev = NULL;
    free(p);
    l->c = l->r;
  } else if(p == l->l){
    l->l = p->prev;
    if(p != l->r)    p->prev->next = NULL;
    free(p);
    l->c = l->l;
  } else {
    l->c = p->prev;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
  }
}

// reverse list
void reversel(llist *l){
  node *z = l->l;
  l->l = l->r;

  while (l->r != NULL) {
    node *temp;
    temp = l->r->next;
    l->r->next = l->r->prev;
    l->r->prev = temp;
    l->r = l->r->prev;
  }
  l->r = z;
}
//count dual node List
int countList(node *r){
  node *p = r;
  int c = 0;
  while (p != NULL) {
    c++;
    p = p ->next;
  }
  return c;
}


// insert begin of list
void insertB(llist *l,ETYPE val){
  node *p;
  p = makeNode(val);

  if(l->r == NULL) {
    l->r = p;
    l->l = p;
    l->c = p;
  } else {
    l->r->prev = p;
    p->next = l->r;
    p->prev = NULL;
    l->r =p;
    l->c = p;
  }
}
// insert at position

node *insertAtPosition(llist *l,ETYPE v,int n){
  if(l->r == NULL ) {
    fprintf(stderr,"\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(l->r) -1) {
    fprintf(stderr,"\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    insertB(l,v);
  } else if(n == countList(l->r)){
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
    return l->c;
  }
  return NULL;
}
// delete at position

node *deleteAtPosition(llist *l,int n){
  if(l->r == NULL ) {
    fprintf(stderr,"\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(l->r) -1) {
    fprintf(stderr,"\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    delNode(l,l->r);
  } else if(n == countList(l->r)){
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
    return l->c;
  }
  return NULL;
}

// Devide list

llist *devideList(llist *l,int p){
  if(l->r == NULL) {
    fprintf(stderr,"Haven't list insert !!\n");
    return NULL;
  }
  if(p < 0 ||  p > countList(l->r) -1){
    fprintf(stderr,"Positon value invaild !!\n");
    return NULL;
  }

  llist *list;
  list = (llist *)malloc(sizeof(llist));
  linit(list);



  int c = 0;
  node *z = l->r->next;
  while (z != NULL) {
    c++;
    if(c == p) break;
    z = z ->next;
  }
  list->r = z->next;
  list->l = l->l;
  list->c = l->l;
  l->l = z;
  l->c = z;
  z->next = NULL;
  return list;
}

// Extract list

void extractList(llist *l,int p,int p2){
  if(l->r == NULL) {
    fprintf(stderr,"Haven't list insert !!\n");
    return ;
  }
  if(p < 0 ||  p > countList(l->r) -1){
    fprintf(stderr,"Positon value invaild !!\n");
    return ;
  }
  if(p2 < 0 ||p +  p2 > countList(l->r) -1){
    fprintf(stderr,"Positon value invaild !!\n");
    return ;

  }
  node *rn = l->r;
  int c = 0;
  node *z = l->r->next;
  while (z != NULL) {
    c++;
    if(c == p) l->r = z;
    if(c == p2 + p ) l->l = z;
    z = z ->next;
  }
  l->c = l->l;
  l->r->prev->next  =NULL;
  freelist(rn);
  freelist(l->l);
  l->l->next = NULL;

}


void mergelist(llist *l,llist *l2){
  l->l->next = l2->r;
  l2->r->prev = l->l;




  l->l = l2 -> l;
  l->c = l->l;


  l2->r =  NULL;
  l2 -> l = NULL;
  l2 -> c = NULL;



}
