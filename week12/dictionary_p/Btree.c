/*
  implemention binary tree with void * type
 */


#include "Btree.h"

void MakeNullTree(tree *t){
  (*t) = NULL;
}

int isEmpty(tree t){
  return t == NULL;
}


tree LeftChild(tree n){
  if( n == NULL) return NULL;
  else return n->left;
}
tree RightChild(tree n){
  if( n == NULL) return NULL;
  else return n->right;
}


nodet * CreateNode(void * v) {
  nodet *new = (nodet *)malloc(sizeof(nodet));
  if(new == NULL) return NULL;
  new->element = v;
  new->left = NULL;
  new->right = NULL;
  new->count = 1;
  return new;
}
int isLeaf(tree n){
  if(n != NULL) return( (LeftChild(n)==NULL) && (RightChild(n)==NULL));
  return -1;
}

int nb_nodes(tree t){
  if(isEmpty(t)) return 0;
  return 1 + nb_nodes(t->left) + nb_nodes(t->right);
}

tree createfrom2(void * e,tree l,tree r){
  nodet * new =(nodet *)malloc(sizeof(nodet));
  if(new != NULL){
    new->element = e;
    new->left = l;
    new->right = r;
    new->count = 1;
  }
  return new;
}

tree Addleft(tree *Tree,void * e){
  nodet *new = CreateNode(e);
  if(new == NULL) return new;
  if(*Tree == NULL) *Tree = new;

  else {
    nodet *L = *Tree;
    while (L->left != NULL) {
      L = L->left;
    }
    L->left = new;
  }
  return new;
}


tree Addright(tree *Tree,void * e){
  nodet *new = CreateNode(e);
  if(new == NULL) return new;
  if(*Tree == NULL) *Tree = new;
  else {
    nodet *R = *Tree;
    while (R->left != NULL) {
      R = R->left;
    }
    R->left = new;
  }
  return new;
}


int nb_leaf(tree t){
  if(t == NULL) return 0;
  else {
    int l = isLeaf(t->left),
      r = isLeaf(t->right);
    int s = 0 ;
    if(l != -1) s += l;
    if(r != -1) s += r;
    return nb_leaf(t->left) + nb_leaf(t->right) + s;
  }
}

int height(tree T){
  if(T == NULL) return 0;
  else{
    return ((height(T->left)+1)>(height(T->right)+1))?(height(T->left)+1):(height(T->right)+1);
  }
}

int depth(tree T,tree cTree,int d){
  if(T == NULL || cTree == NULL) return 0;
  else
    if(T == cTree ) return d;
    else {
      return depth(T->left,cTree,d+1) + depth(T->right,cTree,d+1);
    }
}


int nb_inodes(tree t){
  if(t == NULL) return 0;
  else {
    int l = isLeaf(t->left),
      r = isLeaf(t->right),
      s = 0;
    if(l != -1) s+= (l == 0)?1:0;
    if(r != -1) s+= (r == 0)?1:0;
    return s + nb_inodes(t->left) + nb_inodes(t->right);
  }
}


int nb_right(tree t){
  if(t == NULL) return 0;
  else {
    int s = 0;
    if(t->right != NULL) s = 1;
    return s + nb_right(t->right) + nb_right(t->left);
  }
}



void pre_order(tree t,void (*order)(tree)){
  if(t == NULL) return;
  order(t);
  pre_order(t->left,order);
  pre_order(t->right,order);

}
void in_order(tree t,void (*order)(tree)){
  if(t == NULL) return;
  in_order(t->left,order);
  order(t);
  in_order(t->right,order);

}
void post_order(tree t,void (*order)(tree)){
  if(t == NULL) return;
  post_order(t->left,order);
  post_order(t->right,order);
  order(t);
}


void freetree(tree *t){
  if(t == NULL || *t == NULL) return;
  freetree(&((*t)->left));
  freetree(&((*t)->right));

  if(t != NULL) {
    free((*t)->element);
    free((*t));
  }
  (*t) = NULL;
}


void freetreee(tree *t){
  if(t == NULL || *t == NULL) return;
  freetreee(&((*t)->left));
  freetreee(&((*t)->right));

  if(t != NULL) {
    // free((*t)->element);
    free((*t));
  }
  (*t) = NULL;
}


void reversetree(tree *t){
  if(t == NULL){
    fprintf(stderr,"ERROR in %s:%d \n",__FILE__,__LINE__);
    exit(1);
  }
  if((*t) == NULL) return;
  reversetree(&((*t)->left));
  reversetree(&((*t)->right));
  SWAP((*t)->left,(*t)->right);
}
