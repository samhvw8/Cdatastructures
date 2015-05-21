#include "BST.h"
#include <string.h>
#include <ctype.h>

typedef struct addr$
{
     char word[100];
} word;

typedef word *wordp;


void export(tree r,FILE *f);
#define COLP 3

void printfreq(tree T){
     static int cw = 0;
     if(T == NULL) return ;
     cw++;
     if(cw%COLP != 0){
          int width = 25-strlen(((wordp)(T->element))->word);
          printf("%s[%d%*c ",((wordp)(T->element))->word,T->count,-width,']');  
          printf("\t");
     }
     else printf("%s[%d]\n",((wordp)(T->element))->word,T->count);  
     printfreq(T->left);
     printfreq(T->right);
}
void fixword(char *string);
void exportfrq(tree T,FILE *f){
     static int cw = 0;
     if(T == NULL) return ;
     cw++;
     if(cw%2 != 0){
          int width = 25-strlen(((wordp)(T->element))->word);
          fprintf(f,"%s[%d%*c ",((wordp)(T->element))->word,T->count,-width,']');  
          fprintf(f,"\t");
     }
     else fprintf(f,"%s[%d]\n",((wordp)(T->element))->word,T->count);  
     exportfrq(T->left,f);
     exportfrq(T->right,f);
}



int MAX;
int cmp(const void *a,const void *b);  // compare function

wordp *getword(FILE *f); // get word and trans on file
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
  // #define eclare
     wordp * wordarr;
     
     wordarr = getword(f);
     
     fclose(f);
     qsort(wordarr,MAX,sizeof(wordp),cmp); // sort array
     
     printf("\n");
     
     tree *wordt;
     
     wordt = (tree *)malloc(sizeof(tree));
     
     if(wordt == NULL) {
          fprintf(stderr,"\t\tERROR : Allocate tree failed !! \n");
          exit(1);
     }
     
     MakeNullTree(wordt);
     
     addfarr(wordt,sizeof(wordp),(void **)wordarr,0,MAX-1,cmp); // add array to tree
     
     Balance(wordt,cmp); // Make tree Balance
     
     printfreq(*wordt);
     
     f = fopen("wordcounting.txt", "w");
     if(f == NULL) {
          fprintf(stderr,"\t\tCan't write file %s\n","wordcounting.txt");
          exit(1);
     }
     
     exportfrq(*wordt,f);
     printf("\n");
     fclose(f);
     //free
     
     
     freetree(wordt);
     free(wordarr);
     free(wordt);
     
     
     return 0;
}

wordp *getword(FILE *f){
     // declare
     wordp * wordarr;
     int id;
     MAX = 0;
     
     
     
     while(!feof(f)) {
          char s[1000];
          fscanf(f,"%s",s);
          MAX++;
     }
     MAX--;
     rewind(f);
     
     // ---> allocatce
     wordarr = (wordp*)malloc(sizeof(wordp) * MAX);
     
     for (id = 0; id < MAX; id++) {
          wordarr[id] = (wordp)malloc(sizeof(word));
     }
     // <---
     
     for (id = 0; id < MAX; id++) {
          fscanf(f,"%s",wordarr[id]->word);
          fixword(wordarr[id]->word);
     }
     
     return wordarr;
}

int cmp(const void *a,const void *b){
     char* va = (*(wordp*)a)->word,
          *vb = (*(wordp*)b)->word;
     return strcmp(va,vb);
}
void fixword(char *string){
     int i,j; // index
     
     i = j = 0;
     
     char word[strlen(string)+1];
         
     while (string[i] != '\0') {
          if(isalpha(string[i]) || string[i] == '-'  || 
             string[i] == '_'){
               if(!islower(string[i])){
                    string[i] = string[i] - 'A' + 'a';
               }
               word[j] = string[i];
               j++;        
          }
       i++;
     }
     word[j] = '\0';
     strcpy(string,word);
}
