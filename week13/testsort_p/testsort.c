#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#include "sort.h"
//#define timerun(time,mgr) printf("\n\t\t Time run of %s :  %lf\n",(mgr),(double)(time)/CLOCKS_PER_SEC)

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

void freearr(student ***sarr,int num);

void mfflush() {
     int ch;
     while((ch = getchar()) && ch != '\n' && ch != EOF);
}

int main(int argc, char *argv[]){
     student **s;
     int num;
     if(argc != 2) {
          fprintf(stderr,"\t\t\tERROR :Wrong Input !! \n"
                          "\t\tUSAGE :./testsort <INPUT FILE 1>  \n");
          exit(1);
     }

     FILE *fi;

     if((fi = fopen(argv[1],"r+")) == NULL) {
          fprintf(stderr,"Can't read %s file !!\n",argv[1]);
          exit(1);
     }

     readff(fi,&s,&num);
     printarr(s,num);
     printf("\n\t\t\tStart sort\n");

     // Insertion sort
     printf("\t\tInsertion Sort\n\n");
     insersort((void *)s,num,cmpDic);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Quick sort
     printf("\t\tQuick Sort\n\n");
     readff(fi,&s,&num);
     quicksort((void *)s,0,num-1,cmpDic);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Heap Sort
     printf("\t\tHeap Sort\n\n");
     readff(fi,&s,&num);
     heapsort((void *)s,num,cmpDic);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Merge sort
     printf("\t\tMerge Sort\n\n");
     readff(fi,&s,&num);
     mergesort((void *)s,0,num-1,cmpDic);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Shell sort
     printf("\t\tShell Sort\n\n");
     readff(fi,&s,&num);
     shellsort((void *)s,num,cmpDic);
     printarr(s,num);
     freearr(&s,num);
     printf("\n");

     // Intro sort
     printf("\t\tIntro Sort\n\n");
     readff(fi,&s,&num);
     introsort((void *)s,num,cmpDic);
     printarr(s,num);
     freearr(&s,num);
     printf("\n");



     fclose(fi);



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
  rewind(f);
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
void freearr(student ***sarr,int num){
     long long  i ;

     for (i = 0; i < (num); i++)
          free((*sarr)[i]);

     free(*sarr);
     *sarr = NULL;
}
