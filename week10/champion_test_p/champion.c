#include "Btree.h"
#include <string.h>
#include <time.h>
#define MAX 16// default : 16 player

#define SWAP(x , y) do { typeof(x) SWAP = (x); (x) = (y) ; (y) =SWAP;} while (0);


void printpretty(tree T,FILE *f){
  char space[] = "    ";
  if(T == NULL) return ;
  printpretty(T->left,f);
  int i,h = height(T);
  for (i = 0; i < 3*h; i++) {
    printf("%s",space);
    fprintf(f,"%s",space);
  }
  printf("%-s\n",(char *)T->element);
  fprintf(f,"%-s\n",(char *)T->element);
  printpretty(T->right,f);
}

void printe(tree t){
  if(t == NULL) return;
  printf("%s\n",(char *)t->element);
}

tree *getdata(FILE *s); // return array of pointer node

void suffer(tree *array);

tree match(tree *array,FILE *fo);

void show(tree *array);

int main(int argc, char *argv[])
{
  if(argc != 2){
    fprintf(stderr,"\t\tERROR INPUT\n"
            "./champion <FILE INPUT> \n");
    exit(1);
  }
  // file input
  FILE *fi = fopen(argv[1],"r");
  if(fi == NULL) {
    fprintf(stderr,"\t\tERROR Can't Read file %s\n",argv[1]);
    exit(1);
  }
  // file output
  char foname[] = "Match_for_";
  strcat(foname,argv[1]);
  FILE *fo = fopen(foname,"w");
  if(fo == NULL) {
    fprintf(stderr,"\t\tERROR Can't Create file %s\n",foname);
    exit(1);
  }
  srand((unsigned)time(NULL));
  // get data from file
  tree *tarray = getdata(fi);

  printf("\t\tList Player : \n");
  //show(tarray);

  suffer(tarray); //suffer array

  show(tarray);

  printf("\t\t\t-------------------------\n");
  printf("\t\tMatch :\n");

  tree a = match(tarray,fo);

  printf("\t\t\t-------------------------\n");

  printf("\n");
  printpretty(a,fo);
  printf("\n");

  printf("\t\t\t\t LEVER ORDER TEST :\n");
  level_order(a,printe);


  freetree(&a);

  fclose(fo);
  fclose(fi);
  return 0;
}

tree match(tree *array,FILE *fo){
  int N = MAX;
  tree temp[MAX];
  int i
    ,x = 1;
  // create temp array
  for (i = 0; i < N; i++) {
    temp[i] =  array[i];
  }

  while (N != 1) {
    N = N/2;
    i = 0;
    int z = 0;
    while (i < N*2) {
      int j = rand()%2;
      char *winner = (char *)malloc(sizeof(char)*strlen(temp[i+j]->element));

      if(winner == NULL) {
        fprintf(stderr,"\t\tERROR Malloc fail match function !!");
        exit(1);
      }

      strcpy(winner,temp[i+j]->element);

      tree a = createfrom2(winner,temp[i],temp[i+1]);

      fprintf(fo,"Match %d :%s- %s win : %s \n",x,(char *)temp[i]->element,(char *)temp[i+1]->element,(char *)temp[i+j]->element);
      printf("\tMatch %d : %s \n \t\t   %s  \n \t\t   win : %s \n",x,(char *)temp[i]->element,(char *)temp[i+1]->element,(char *)temp[i+j]->element);
      if(x == 15 ) {
        fprintf(fo,"\t\t --> Champion %s <--\n",(char *)temp[i+j]->element);
        fprintf(stdout,"\n\t\t --> Champion %s \n",(char *)temp[i+j]->element);
      }
        x++;
      temp[z] = a;
      z++;
      i+=2;
    }
  }
  free(array);
  array = NULL;
  tree *result = (tree *)malloc(sizeof(tree));
  *result = temp[0];
  return *result;
}

void suffer(tree *array){
  int i;
  for (i = 1; i < MAX; i++) {
    int randpos = rand()%i;
    SWAP(array[randpos],array[i]);
  }
}

tree *getdata(FILE *s){
  tree *tarray = (tree *)malloc(sizeof(tree) * MAX);
  int c = 0;

  while (c < MAX) {
    char *ss = (char *)malloc(sizeof(char)*30);
    fscanf(s,"%[^\n]\n",ss);

    // if(c == (MAX - 1)) {
    //  ss[strlen(ss)] = '\n';
      //   ss[strlen(ss)+1] = '\0';
    //  }
    tarray[c] = CreateNode(ss);
    c++;
  }

  return tarray;
}


void show(tree *array){
  int i;
  for (i = 0; i < MAX; i++) {
    printf("\t%s \n",(char *)array[i]->element);
  }

}
