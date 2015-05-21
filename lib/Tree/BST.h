/*
  Author : Ginz
  Binary search tree with void * type
  
  left is smaller // right is larger

 */



#ifndef _BST_GIN_H_
#define _BST_GIN_H_
#define cNULL(X) (X) == NULL 
#define cNNULL(X) (X) != NULL
#ifndef SWAP
#define SWAP(x , y) do { typeof(x) SWAP = (x); (x) = (y) ; (y) =SWAP;} while (0);
#endif
#ifndef PERROR
#define PERROR fprintf(stderr,"\t\tERROR in %s:%d\n",__FILE__,__LINE__)
#endif


#include "Btree.h"

void insert(tree *root,void *key,int (*cmp)(const void *,const void *));
tree *search(tree *root,void *fkey,int (*cmp)(const void *,const void *));
void addfarr(tree *r,size_t size,void * *arr,int L,int R,int (*cmp)(const void*,const void*));
tree *findmin(tree *root);
tree *findmax(tree *root);
void deletemin(tree *root,void *key,int (*cmp)(const void *,const void *));
void fixbalance(tree *r,int h);
void checkBSTcondition(tree *r,int (*cmp)(const void *,const void *));
#define Balance(r,cmp) fixbalance(r,height(*r));     \
checkBSTcondition(r,cmp);

int lowertkey(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t));
int highertkey(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t));

int postHK(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t));
int postLK(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t));
#endif
