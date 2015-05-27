/*
 * Author : Ginz
 * Binary tree with void * type
 */

#ifndef _Btree_H_GIN_
#define _Btree_H_GIN_
#include <stdio.h>
#include <stdlib.h>

#ifndef SWAP
#define SWAP(x , y) do { typeof(x) TEMP = (x); (x) = (y) ; (y) =TEMP;} while (0);
#endif

typedef struct nodet  nodet;
typedef struct nodet {
  void * element;
  nodet *left,
    *right;
  int count;
} nodet;

typedef nodet *tree;

tree LeftChild(tree n);
tree RightChild(tree n);
nodet * CreateNode(void * v);
int isLeaf(tree n);

void MakeNullTree(tree *t);

// check empty if empty return 1 else 0
int isEmpty(tree t);

// number of node
int nb_nodes(tree t);
// number of leaf
int nb_leaf(tree t);

// create tree from 2 subtree and element
tree createfrom2(void * e,
                     tree l,
                     tree r);
// add to left most
tree Addleft(tree *Tree,
                 void * e);

// add to right most
tree Addright(tree *Tree,
                  void * e);

// height of tree

int height(tree T);

// depth of tree

int depth(tree T,tree cTree,int d);


// number of internal node
int nb_inodes(tree t);


// number of right node
int nb_right(tree t);


void pre_order(tree t,void (*order)(tree));
void in_order(tree t,void (*order)(tree));
void post_order(tree t,void (*order)(tree));
void freetree(tree *t);

void reversetree(tree *t);

#endif
