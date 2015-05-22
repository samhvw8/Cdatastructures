
#include "linkstack.h"

//make node
nodes *makeNode(void * val){
  nodes *p = NULL;
  p  = (nodes *)malloc(sizeof(nodes));
  if(p != NULL){
    p->next = NULL;
    p->v = val;
    return p;
  } else return NULL;
}


// del first node p
void dfnode(nodes **r){
  if(r == NULL) return ;
  if(*r == NULL) return ;
  nodes *p; p  = *r;
    *r = p->next;
  free(p);
}


// insert node begin of list
void inodeB(nodes *p,nodes **r){
  if(r == NULL) return ;
  if(*r == NULL) {
    *r = p;
  } else {
    p->next = *r;
    *r =p;
  }
}

// free list
void freelist(nodes **r){
  if (r == NULL) return;
  if (*r == NULL) return;
  nodes *to_free = *r;
  while(to_free != NULL){
    *r = (*r)->next;
    free(to_free);
    to_free = *r;
  }
}

void Sinstall(stackp stack){
  *stack = NULL;
}

void Sremove(stackp stack){
  if(stack != NULL) freelist(stack);
}
int empty(stack stack){
     return stack == NULL;
}
void push(void * el,stackp stack){
     nodes *p = makeNode(el);
     inodeB(p,stack);
}
void * pop(stackp stack){
     if(!empty(*stack)) {
          void * a = (*stack)->v;
          dfnode(stack);
          return a;
     } else {
          printf("\tStack Underflow !!\n");
          return NULL;
     }
}
