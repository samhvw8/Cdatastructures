#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"


typedef struct student_t{
     int no,
          mssv;
     char name[30],
          tel[15];
} student;

int sizefile(FILE *f);
void readff(FILE *f,student ***sarr,int *num);

int cmpDic(const void *a,const void *b);
void printarr(student **sarr,int num);



void mfflush() {
  int ch;
  while((ch = getchar()) && ch != '\n' && ch != EOF);
}

int main(int argc, char *argv[]){
  student **s;
  int num;
  if(argc != 2) printf("Wrong Input !! \n"
                       " USAGE :./tsort <INPUT FILE 1>  \n");
  else {
    FILE *fi;
    if((fi = fopen(argv[1],"r+")) == NULL) {
      fprintf(stderr,"Can't read %s file !!\n",argv[1]);
      exit(1);
    }
    readff(fi,&s,&num);
    printarr(s,num);
// insersort((void *)s,num,cmpDic);
   quicksort((void *)s,0,num-1,cmpDic);
//    heapsort((void *)s,num,cmpDic);
    printf("\n\n\n");
    printarr(s,num);

    fclose(fi);
    free(s);

  }
  return 0;
}


// size of file

int sizefile(FILE *f){
  int a = 0;
  char buff[1000];
  while (fgets(buff,1000,f) != NULL) {
    a++;
  }
  rewind(f);
  return a;
}
// read from file
void readff(FILE *f,student ***sarr,int *num){
  int i;
  *num = sizefile(f);

  *sarr = (student **)malloc((*num)*sizeof(student*));
  if(*sarr == NULL) {
       fprintf(stderr,"ERROR IN %s:%d\n",__FILE__,__LINE__);
       exit(1);
  }
  for (i = 0; i < (*num); i++) {
       (*sarr)[i] = (student *)malloc(sizeof(student));
       if(((*sarr)[i]) == NULL) {
            fprintf(stderr,"ERROR IN %s:%d\n",__FILE__,__LINE__);
            exit(1);
       }

  }

  for (i = 0; i < (*num); i++) {
    (*sarr)[i]->no = i;
    fscanf(f,"%d|%[^|]|%s[^\\]",&((*sarr)[i]->mssv),(*sarr)[i]->name,(*sarr)[i]->tel);
  }

  /* for (i = 0; i < (*num); i++) { */
  /*   printf("%-3d - %d - %-30s - %-15s\n",(*sarr)[i].no,(*sarr)[i].mssv,(*sarr)[i].name,(*sarr)[i].tel); */
  /* } */
}

void printarr(student **sarr,int num){
     int i;
     for (i = 0; i < num; i++) {
          printf("%-3d - %d - %-30s - %-15s\n",(sarr)[i]->no,(sarr)[i]->mssv,(sarr)[i]->name,(sarr)[i]->tel);
     }

}



// cmp in qsort
int cmpDic(const void *a,const void *b){
  student *za = *(student **)a;
  student *zb = *(student **)b;
  return strcmp(za->name,zb->name);
}
