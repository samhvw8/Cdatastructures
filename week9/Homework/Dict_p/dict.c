#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dict$
{
  char key[30];
} dict;


size_t num;


size_t sizefile(FILE *f);
void readff(FILE *f,dict *arr);
int rBinSearch(dict *L,char *Target,int Lo,int Hi);
void checkkey(dict *L);



int main(int argc, char *argv[])
{
  FILE *fi;

  if( (fi = fopen("//usr//share//dict//words","r")) == NULL ){
    fprintf(stderr,"\t\t[ERROR] Can't Read file %s \n","//usr//share//dict//words");
    exit(1);
  }

  num = sizefile(fi);
  dict *Dict;
  Dict = (dict *)malloc(sizeof(dict)*num);
  if(Dict == NULL){
    fprintf(stderr,"\t\t[ERROR] Can't Allocate memory !!\n");
    exit(1);
  }
  // load data into dynamic array
  readff(fi,Dict);
  checkkey(Dict);


  fclose(fi);
  free(Dict);
  return  0;
}

void checkkey(dict *L){
  char buff[30];
  printf("\n\t\t Keyword Search :");scanf("%s",buff);
  int loc = rBinSearch(L,buff,0,num-1);
  if(loc != -1) printf("\t\t Found keyword %s in dictionary at location %d \n",buff,loc);
  else printf("\t\tkeyword %s not found in dictionary  \n",buff);
}






// binary search for Dict
int rBinSearch(dict *L,char *Target,int Lo,int Hi){
  if(Hi == Lo) if(strcmp(L[Hi].key,Target) == 0) return Hi; else return -1;
  if(Lo > Hi) return -1;
  int Mid = (Lo + Hi)/2;
  int f = 0;
  if((f = strcmp(L[Mid].key,Target) ) == 0) return Mid;
  else if(f > 0) rBinSearch(L,Target,Lo,Mid - 1);
  else return rBinSearch(L,Target,Mid + 1,Hi);
}




void readff(FILE *f,dict *arr){

  int i;
  for (i = 0; i < num; i++) {
    fscanf(f,"%s",arr[i].key);
  }

}

size_t sizefile(FILE *f){
  size_t a = 0;
  char buff[1000];
  while (fgets(buff,1000,f) != NULL) {
    a++;
  }
  rewind(f);
  return a;
}

