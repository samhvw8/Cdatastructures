/*
  Author : Ginz 
  
  implement of BST tree 
  
  left is smaller // right is larger
*/

#include "BST.h"
tree *findmin(tree *root){
     if((*root) == NULL ||root == NULL) return NULL;
     if((*root)->left == NULL) return root;
     return findmin(&((*root)->left));
}

tree *findmax(tree *root){
     if((*root) == NULL||root == NULL) return NULL;
     if((*root)->right == NULL) return root;
     return findmax(&((*root)->right));
}

void insert(tree *root,void *key,int (*cmp)(const void *,const void *)){
     
     if(key == NULL || root == NULL) {
          PERROR;
          exit(1);
     }
     if ((*root) == NULL) {
          *root = CreateNode(key);
          return;
     } 
     
     int c;
     if((c = cmp(&key,&((*root)->element))) < 0) insert(&((*root)->left),key,cmp);
     else if(c > 0) insert(&((*root)->right),key,cmp);
     else if(c == 0) {
          ((*root)->count)++;
          free(key);
     }
}

tree *search(tree *root,void * fkey,int (*cmp)(const void *,const void *)){
     if(root == NULL || *root == NULL || fkey == NULL) return NULL;
     int c;
     if((c = cmp(&fkey,&((*root)->element))) == 0) return (root);
     else if(c  < 0) return search(&((*root)->left),fkey,cmp);
     return search(&((*root)->right),fkey,cmp);
     
}

void deletemin(tree *root,void *key,int (*cmp)(const void *,const void *)){
     if(key == NULL || root == NULL) {
          PERROR;
          exit(1);
     }
     if(*root == NULL) {
          return ;
     }
     tree * found = search(root,key,cmp); 
     if(found == NULL || *found == NULL ) {
          fprintf(stderr,"ERROR : not found key !! \n");
          return ;
     }
     
     else {
          if(((*found)->count) > 1) {
               ((*found)->count)--;
               return ;
          }
          if(isLeaf(*found)) { // if leaf
               free((*found)->element); // free key
               free((*found)); // free node
               (*found) = NULL;
               return ;
          }
          else {
               if((*found)->left == NULL || (*found)->right == NULL) {
                    if((*found)->left == NULL) {
                         tree del = (*found);
                         (*found) = (*found)->right;
                         free(del->element);
                         free(del);
                    } 
                    if((*found)->right == NULL) {
                         tree del = (*found);
                         (*found) = (*found)->left;
                         free(del->element);
                         free(del);
                    }        
               } else {
                    tree *min = findmin(&((*found)->right)); // find min
                    
                    if(!isLeaf(*min)) {
                         
                         tree *max = findmax(&((*found)->left));
                         if(!isLeaf(*max)){
                              if(nb_nodes((*found)->right) > nb_nodes((*found)->left)) {
                                   SWAP((*found)->element,(*min)->element);
                                   tree del = *min;
                                   (*min) = (*min)->right;
                                   free((del)->element);
                                   free((del));
                                   (del) = NULL;
                              } else {
                                   SWAP((*found)->element,(*max)->element);
                                   tree del = *max;
                                   (*max) = (*max)->left;
                                   free((del)->element);
                                   free((del));
                                   (del) = NULL;
                              }
                         } else {
                              SWAP((*max)->element,(*found)->element);                 
                              free((*max)->element);
                              free((*max));
                              (*max) = NULL;
                         }
                    }
                    else {
                         SWAP((*min)->element,(*found)->element);                 
                         free((*min)->element);
                         free((*min));
                         (*min) = NULL;
                    }
               }
          }  
     }
}

void addfarr(tree *r,void * *arr,int L,int R,int (*cmp)(const void*,const void*)){
     if(arr == NULL || * arr == NULL) return ;
     if( L > R) return ;
     
     if( L == R) return insert(r,arr[L],cmp);
     
     int m = (L + R)/2 + 1;
     insert(r,arr[m],cmp);
     addfarr(r,arr,L,m-1,cmp);
     addfarr(r,arr,m+1,R,cmp);  
     
}

void fixbalance(tree *r,int h){
     if(r == NULL || *r == NULL ) return ;
     if( h == 3 || h == 4){
          if(cNNULL((*r)->left) && cNNULL((*r)->right) && 
             cNNULL((*r)->left->left) && cNNULL((*r)->right->right) &&
             cNULL((*r)->left->right) && cNULL((*r)->right->left)){
               
               (*r)->left->right = (*r);
               tree oldroot =  (*r);
               (*r) = (*r)->left;
               oldroot->left = NULL;
          }
          if((cNULL((*r)->left) && 
              cNNULL((*r)->right))||((cNULL((*r)->right)) && 
                                     cNNULL((*r)->left))){
               
               if(cNULL((*r)->left) && cNNULL((*r)->right) && 
                  cNNULL((*r)->right->right)) {
                    SWAP((*r)->element,(*r)->right->element); 
                    SWAP((*r)->right->right,(*r)->left); 
                    SWAP((*r)->left->element,(*r)->right->element); 
                    
               } else {
                    if(cNULL((*r)->right) && cNNULL((*r)->left) && 
                       cNNULL((*r)->left->left)){
                         SWAP((*r)->element,(*r)->left->element); 
                         SWAP((*r)->left->left,(*r)->right); 
                         SWAP((*r)->right->element,(*r)->left->element); 
                    }
               }
               //
               if(cNULL((*r)->left) && cNNULL((*r)->right) && 
                  cNNULL((*r)->right->left)) {
                    SWAP((*r)->element,(*r)->right->element); 
                    SWAP((*r)->right->left,(*r)->left); 
                    SWAP((*r)->left->element,(*r)->right->element); 
                    
               } else {
                    if(cNULL((*r)->right) && cNNULL((*r)->left) && 
                       cNNULL((*r)->left->right)){
                         SWAP((*r)->element,(*r)->left->element); 
                         SWAP((*r)->left->right,(*r)->right); 
                         SWAP((*r)->right->element,(*r)->left->element); 
                    }
               }
               
          }
     } 
     fixbalance(&((*r)->left),h-1);
     fixbalance(&((*r)->right),h-1);
}

void checkBSTcondition(tree *r,int (*cmp)(const void *,const void *)){
     if( r == NULL) {
          PERROR;
          exit(1);
     }
     if(*r == NULL) return ;
     checkBSTcondition(&((*r)->left),cmp);
     checkBSTcondition(&((*r)->right),cmp); 
     if(cNNULL((*r)->left))if(cmp(&((*r)->element),&((*r)->left->element)) < 0) SWAP((*r)->element,(*r)->left->element);
     if(cNNULL((*r)->right))if(cmp(&((*r)->element),&((*r)->right->element)) > 0) SWAP((*r)->element,(*r)->right->element);
     
}


////// Lower Key && Higher Key //////


int lowertkey(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t)){
     if(root == NULL );
     else if(key == NULL){
          PERROR;
          exit(1);
     }
     printf("\t\t Lower than key is :\n\t\t");
     return postLK(root,key,cmp,visit);
}

// suport function
int postLK(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t)){
     if(key == NULL) {
          PERROR;
          exit(1);
     }
     if(root == NULL) return 0;

     int c = cmp(&key,&(root->element));
     if(c > 0){ // if key > root->element
          visit(root);
          return 1 + postLK(root->left,key,cmp,visit)  +  postLK(root->right,key,cmp,visit);
     }
     return postLK(root->left,key,cmp,visit)  +  postLK(root->right,key,cmp,visit);
}

int highertkey(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t)){
     if(root == NULL );
     else if(key == NULL){
          PERROR;
          exit(1);
     }
     printf("\t\t Higher than key is :\n\t\t");
     return postHK(root,key,cmp,visit);
}

int postHK(tree root,void *key,int (*cmp)(const void *,const void *),void (*visit)(tree t)){
     if(key == NULL) {
          PERROR;
          exit(1);
     }
     if(root == NULL) return 0;

     int c = cmp(&key,&(root->element));
     if(c < 0){ // if key < root->element
          visit(root);
          return 1 + postHK(root->left,key,cmp,visit)  +  postHK(root->right,key,cmp,visit);
     }
     return postHK(root->left,key,cmp,visit)  +  postHK(root->right,key,cmp,visit);
}
