#include "BST.h"
#include <time.h>

#define MAX 30

#define MAKEP(v,p) typeof(v) * p; \
  p = (typeof(v) *)malloc(sizeof(typeof(v))); \
  *p = v; \

void printpretty(tree r,tree T,int m){
  char space[] = "    ";
  if(T == NULL) return ;
  printpretty(r,T->left,m);
  int i,h = m - depth(r,T,0);
  for (i = 0; i < 2*h; i++) {
    printf("%s",space);
  }
  printf("%d\n",*(int *)T->element);
  printpretty(r,T->right,m);
}

void printe(tree r){
  if(r == NULL) return ;
  printf("%d ",*(int *)r->element);
}

int intcom(const void *a,const void *b){
  return **(int **)a - **(int **)b;
}

int main(){
  
  srand((unsigned)time(NULL));
  
  tree * inttree;
  
  inttree = (tree *)malloc(sizeof(tree));
  if(inttree == NULL) {
    fprintf(stderr,"ERROR allocate fail \n");
    exit(1);
  }


  MakeNullTree(inttree);
  int * * c,i;
  c = (int **)malloc(sizeof(int*)*MAX);
  
  for (i = 0; i< MAX;i++) {
    (c[i]) = (int *)malloc(sizeof(int));
  }
  
  for (i = 0; i< MAX;i++) *c[i] = i;

  for (i = 0; i< MAX;i++) printf("%d ",*c[i]);
  
  addfarr(inttree,sizeof(int),(void **)c,0,MAX-1,intcom);
  


  printf("\n");  
  printpretty(*inttree,*inttree,height(*inttree));
  printf("\n");
  pre_order(*inttree,printe);
  printf("\n");

  printf("\t\t------------- FIX balance !! --------------\n");
  Balance(inttree,intcom);

  printf("\n");  
  printpretty(*inttree,*inttree,height(*inttree));
  printf("\n");
  pre_order(*inttree,printe);
  printf("\n");

    
  
  int findv = 0;
  
  while (1) {
    printf("\t\t Search key : ");
    scanf("%d",&findv);
    if(findv == -1) break;
    tree *findn = search(inttree,&findv,intcom);
    if(findn == NULL) {
      printf("\t\t value %d not found !!\n",findv);
      continue;
    }
    printf("\t\t value %d found on tree !!\n",findv);
  }
  
  
  while (1) {
    if( *inttree == NULL) {
      fprintf(stdout,"\t\t Tree is empty !!\n");
      break;
    }
    printf("\t\t Delete key : ");
    scanf("%d",&findv);
    if(findv == -1) break;
    
    deletemin(inttree,&findv,intcom);
    Balance(inttree,intcom);
    printf("\n");  
    
    printpretty(*inttree,*inttree,height(*inttree));
    printf("\n");
    pre_order(*inttree,printe);
    printf("\n");
  }
  


  while (1) {
       if( *inttree == NULL) {
            fprintf(stdout,"\t\t Tree is empty !!\n");
            break;
       }
       printf("\t\t Lower than key : ");
       scanf("%d",&findv);
       if(findv == -1) break;
       int nb = lowertkey(*inttree,&findv,intcom,printe);
       if(nb != -1) {
            if(nb != 0)printf("\n\t\tNumber lower is %d\n",nb);
            else printf("\t\tHaven't lower key !!\n");
       }
              
  }

  while (1) {
       if( *inttree == NULL) {
            fprintf(stdout,"\t\t Tree is empty !!\n");
            break;
       }
       printf("\t\t High than key : ");
       scanf("%d",&findv);
       if(findv == -1) break;
       int nb = highertkey(*inttree,&findv,intcom,printe);
       if(nb != -1) {
            if(nb != 0)printf("\n\t\tNumber higher is %d\n",nb);
            else printf("\t\tHaven't higher key !!\n");
       }
              
  }

  freetree(inttree);
  


  printf("\t\tEXIT PROGRAM !!\n");
  
  return 0;
}
