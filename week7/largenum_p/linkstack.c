
#include "linkstack.h"
//make node
node *makeNode(ETYPE val){
  node *p = NULL;
  p  = (node *)malloc(sizeof(node));
  if(p != NULL){
    p->next = NULL;
    p->v = val;
    return p;
  } else return NULL;
}


// del first node p
void dfnode(node **r){
  if(r == NULL) return ;
  if(*r == NULL) return ;
  node *p; p  = *r;
    *r = p->next;
  free(p);
}


// insert node begin of list
void inodeB(node *p,node **r){
  if(r == NULL) return ;
  if(*r == NULL) {
    *r = p;
  } else {
    p->next = *r;
    *r =p;
  }
}

// free list
void freelist(node **r){
  if (r == NULL) return;
  if (*r == NULL) return;
  node *to_free = *r;
  while(to_free != NULL){
    *r = (*r)->next;
    free(to_free);
    to_free = *r;
  }
}

void Sinstall(StackType *stack){
  *stack = NULL;
}

void Sremove(StackType *stack){
  if(stack != NULL) freelist(stack);
}
int empty(StackType stack){
  return stack == NULL;
}
void push(Eltype el,StackType *stack){
  node *p = NULL;
   p = makeNode(el);
   if(p != NULL)inodeB(p,stack);
   else printf("\tStack overflow !! \n");
}
Eltype pop(StackType *stack){
  if(!empty(*stack)) {
    Eltype a = (*stack)->v;
    dfnode(stack);
    return a;
  } else {
    printf("\tStack Underflow !!\n");
    
  }
}
