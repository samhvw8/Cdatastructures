#include "BST.h"
#include "Ginz.h"
#include <string.h>


typedef struct addr$
{
  char name[30];
  char phone[30];
  char email[30];
} addr;

typedef addr *addrp;


void export(tree r,FILE *f);

void printpretty(tree r,tree T,int m){
  char space[] = "    ";
  if(T == NULL) return ;
  printpretty(r,T->left,m);
  int i,h = m - depth(r,T,0);
  
  for (i = 0; i < 2*h; i++) {
    printf("%s",space);
  }
  
  printf("%s\n",((addrp)(T->element))->email);
  printpretty(r,T->right,m);
}


int MAX;
int cmp(const void *a,const void *b);  // compare function
int countLine(FILE *f); // count line on file
addrp *getAddr(FILE *f); // get addr and trans on file
int main(int argc, char *argv[])
{
  // check input
  if(argc != 2) {
    fprintf(stderr,"\t\tERROR : Wrong fomat \n"
            "\t\t Format : ./dict <FILE INPUT>\n");
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  if(f == NULL) {
    fprintf(stderr,"\t\tCan't Read file %s\n",argv[1]);
    exit(1);
  }
  // declare
  addrp * addrarr;

  addrarr = getAddr(f);


  fclose(f);
  qsort(addrarr,MAX,sizeof(addrp),cmp); // sort array

  printf("\n");
  /* Check sorted array
  for (i = 0; i < MAX; i++) {
    printf("%s - %s\n" ,addrarr[i]->word,addrarr[i]->translate);
  }
  */


  tree *Addrtree;
 
  Addrtree = (tree *)malloc(sizeof(tree));

  if(Addrtree == NULL) {
    fprintf(stderr,"\t\tERROR : Allocate tree failed !! \n");
    exit(1);
  }

  MakeNullTree(Addrtree);

  addfarr(Addrtree,sizeof(addrp),(void **)addrarr,0,MAX-1,cmp); // add array to tree

  Balance(Addrtree,cmp); // Make tree Balance


 printpretty(*Addrtree,*Addrtree,height(*Addrtree)); // Print Tree

 printf("\n");
 f = fopen("test.bin", "wb");
  if(f == NULL) {
    fprintf(stderr,"\t\tCan't Read file %s\n","test.bin");
    exit(1);
  }
 export(*Addrtree,f);
 printf("\t\tExport Complete !!\n");
  return 0;
}

int countLine(FILE *f){
  char buff[1000];
  int c = 0;
  while (fgets(buff,1000,f))  c++;
  return c;
}

addrp *getAddr(FILE *f){
  // declare
  addrp * addrarr;
  int id;
  MAX = countLine(f) - 1;
  rewind(f);

  // ---> allocatce
  addrarr = (addrp*)malloc(sizeof(addrp) * MAX);

  for (id = 0; id < MAX; id++) {
    addrarr[id] = (addrp)malloc(sizeof(addr));
  }
  // <---

  for (id = 0; id < MAX; id++) {
    fscanf(f,"%[^-]-%[0-9]-%[^\n]\n",addrarr[id]->name,addrarr[id]->phone,addrarr[id]->email);
  }


  return addrarr;
}

int cmp(const void *a,const void *b){
  char* va = (*(addrp*)a)->email,
    *vb = (*(addrp*)b)->email;
  return strcmp(va,vb);
}



void export(tree r,FILE *f){
  if(r == NULL || f == NULL) return ;
  fwrite(((addrp)(r->element)),1,sizeof(addr),f);
  export(r->left,f);
  export(r->right,f);
}
