#include "BST.h"
#include "Ginz.h"
#include <string.h>


typedef struct key$
{
  char word[30];
  char translate[30];
} key;

typedef key *keyp;


void export(tree r,FILE *f);

void printpretty(tree r,tree T,int m){
  char space[] = "    ";
  if(T == NULL) return ; //
  printpretty(r,T->left,m);
  int i,h = m - depth(r,T,0);
  for (i = 0; i < 2*h; i++) {
    printf("%s",space);
  }
  printf("%s\n",((keyp)(T->element))->word);
  printpretty(r,T->right,m);
}


int MAX;
int cmp(const void *a,const void *b);  // compare function
int countLine(FILE *f); // count line on file
keyp *getDict(FILE *f); // get key and trans on file
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
  keyp * keyarr;

  keyarr = getDict(f);
  // int i;

  /* Check Import from file
  for (i = 0; i < MAX; i++) {
    printf("%s - %s\n" ,keyarr[i]->word,keyarr[i]->translate);
  }
  */
  fclose(f);
  qsort(keyarr,MAX,sizeof(keyp),cmp); // sort array

  printf("\n");
  /* Check sorted array
  for (i = 0; i < MAX; i++) {
    printf("%s - %s\n" ,keyarr[i]->word,keyarr[i]->translate);
  }
  */


  tree *wordtree;
  key *a;
  tree *b;
  keyp keyadd;
  wordtree = (tree *)malloc(sizeof(tree));

  if(wordtree == NULL) {
    fprintf(stderr,"\t\tERROR : Allocate tree failed !! \n");
    exit(1);
  }

  MakeNullTree(wordtree);

  addfarr(wordtree,sizeof(keyp),(void **)keyarr,0,MAX-1,cmp); // add array to tree

  Balance(wordtree,cmp); // Make tree Balance

  while (1) {
    switch(getmenu("Show;Trans;Add;Delete;Edit;Export",6,1)){
    case 1:

      printpretty(*wordtree,*wordtree,height(*wordtree)); // Print Tree

      printf("\n");
      break;

    case 2:

      a = (key *)malloc(sizeof(key));
      if(a == NULL) {
        printf("\t\tAlocate failed \n");
      } else {
        printf("\t\tWord Search :");scanf("%[^\n]",a->word);mfflush();
        b = search(wordtree,a,cmp);
        if(b == NULL) {
          printf("\t\tNot found Word %s",a->word);
        }else{
          printf("\t\tTrans : %s \n",((keyp)((*b)->element))->translate);
        }
      }
      break;

    case 3:
      keyadd = (keyp)malloc(sizeof(key));

      if(keyadd == NULL) {
        fprintf(stderr,"\t\tAllocate Failed !!\n");
        exit(1);
      }
      printf("\t\tAdd Word : ");scanf("%[^\n]",keyadd->word);mfflush();
      printf("\t\tAdd Trans for %s : ",keyadd->word);scanf("%[^\n]",keyadd->translate);mfflush();
      insert(wordtree,keyadd,cmp);
      break;
    case 4:

      a = (key *)malloc(sizeof(key));
      if(a == NULL) {
        printf("\t\tAlocate failed \n");

      } else {
        printf("\t\tWord Delete :");scanf("%[^\n]",a->word);mfflush();
        deletemin(wordtree,a,cmp);
      }
      break;
    case 5:
      a = (key *)malloc(sizeof(key));
      if(a == NULL) {
        printf("\t\tAlocate failed \n");

      } else {
        printf("\t\tWord want to edit :");scanf("%[^\n]",a->word);mfflush();
        b = search(wordtree,a,cmp);
        if(b == NULL) {
          printf("\t\tNot found %s",a->word);
        }else{
          if((getmenu("Edit Word;Edit Translate",2,0)) == 1) {
            printf("\tWord : %s --> ",((keyp)((*b)->element))->word);
            scanf("%[^\n]",((keyp)((*b)->element))->word);
            mfflush();
          } else {
            printf("\tTrans of word %s --> ",((keyp)((*b)->element))->word);
            scanf("%[^\n]",((keyp)((*b)->element))->translate);
            mfflush();
          }
        }
      }
      break;

    case 6:
      remove(argv[1]);

      f = fopen(argv[1], "w");
      if(f == NULL) {
        fprintf(stderr,"\t\tCan't Create file %s\n",argv[1]);
      } else {
        export(*wordtree,f);
        fprintf(f,"\n");
        printf("\t\t Export Complete !!\n");
      }
      fclose(f);
      break;
    case 0:
      freetree(wordtree);
      free(keyarr);
      free(wordtree);
      return 0;
    }
  }

  return 0;
}

int countLine(FILE *f){
  char buff[1000];
  int c = 0;
  while (fgets(buff,1000,f))  c++;
  return c;
}

keyp *getDict(FILE *f){
  // declare
  keyp * keyarr;
  int id;
  MAX = countLine(f);
  rewind(f);

  // ---> allocatce
  keyarr = (keyp*)malloc(sizeof(keyp) * MAX);

  for (id = 0; id < MAX; id++) {
    keyarr[id] = (keyp)malloc(sizeof(key)); //
  }
  // <---

  for (id = 0; id < MAX; id++) {
    fscanf(f,"%[^-]-%[^-\n]\n",keyarr[id]->word,keyarr[id]->translate);
  }


  return keyarr;
}

int cmp(const void *a,const void *b){
  char* va = (*(keyp*)a)->word,
    *vb = (*(keyp*)b)->word;
  return strcmp(va,vb);
}



void export(tree r,FILE *f){
  if(r == NULL || f == NULL) return ;
  fprintf(f,"%s-%s\n",((keyp)(r->element))->word,((keyp)(r->element))->translate);
  export(r->left,f);
  export(r->right,f);
}
