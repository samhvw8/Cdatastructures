#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#include "sort.h"
//#define timerun(time,mgr) printf("\n\t\t Time run of %s :  %lf\n",(mgr),(double)(time)/CLOCKS_PER_SEC)

typedef struct phone${
     char model[40];
     int size;
     float screen;
     int price;
} phone;

#define DAT "nokiaDB.dat"


int sizefile(FILE *f);
void readff(FILE *f,phone ***parr,int *num);

int cmpphone(const void *a,const void *b);
void printarr(phone **parr,int num);

void freearr(phone ***parr,int num);

void mfflush() {
     int ch;
     while((ch = getchar()) && ch != '\n' && ch != EOF);
}

int main(){
     phone **s;
     int num;

     FILE *fi;

     if((fi = fopen(DAT,"rb+")) == NULL) {
          fprintf(stderr,"Can't read %s file !!\n",DAT);
          exit(1);
     }

     readff(fi,&s,&num);
     printf("Number :%d\n",num);
     printarr(s,num);
     printf("\n\t\t\tStart sort\n");
/*
     // Insertion sort
     printf("\t\tInsertion Sort\n\n");
     insersort((void *)s,num,cmpphone);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Quick sort
     printf("\t\tQuick Sort\n\n");
     readff(fi,&s,&num);
     quicksort((void *)s,0,num-1,cmpphone);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");
*/
     // Heap Sort
     printf("\t\tHeap Sort\n\n");
    // readff(fi,&s,&num);
     heapsort((void *)s,num,cmpphone);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");
/*
     // Merge sort
     printf("\t\tMerge Sort\n\n");
     readff(fi,&s,&num);
     mergesort((void *)s,0,num-1,cmpphone);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Shell sort
     printf("\t\tShell Sort\n\n");
     readff(fi,&s,&num);
     shellsort((void *)s,num,cmpphone);
     printarr(s,num);
     freearr(&s,num);
     printf("\n");

     // Intro sort
     printf("\t\tIntro Sort\n\n");
     readff(fi,&s,&num);
     introsort((void *)s,num,cmpphone);
     printarr(s,num);
     freearr(&s,num);
     printf("\n");
*/


     fclose(fi);



     return 0;
}


// size of file

int sizefile(FILE *f){
     int prev = ftell(f);
     fseek(f,(long)0,SEEK_END);
     int size = ftell(f);
     fseek(f,prev,SEEK_SET);
     return size;
}
// read from file
void readff(FILE *f,phone ***parr,int *num){
     int i;
     *num = sizefile(f)/sizeof(phone);

     *parr = (phone **)malloc((*num)*sizeof(phone*));
     if(*parr == NULL) {
          fprintf(stderr,"ERROR IN %s:%d\n",__FILE__,__LINE__);
          exit(1);
     }
     for (i = 0; i < (*num); i++) {
          (*parr)[i] = (phone *)malloc(sizeof(phone));
          if(((*parr)[i]) == NULL) {
               fprintf(stderr,"ERROR IN %s:%d\n",__FILE__,__LINE__);
               exit(1);
          }

     }

     for (i = 0; i < (*num); i++) {
          fread((*parr)[i],sizeof(phone),1,f);
     }
     rewind(f);
  /* for (i = 0; i < (*num); i++) { */
  /*   printf("%-3d - %d - %-30s - %-15s\n",(*parr)[i].no,(*parr)[i].mssv,(*parr)[i].name,(*parr)[i].tel); */
  /* } */
}

void printarr(phone **parr,int num){
     int i;
     for (i = 0; i < num; i++) {
          printf("%-40s | %-3d gb | %-3.1f '' |%-10d VND\n",
                 (parr)[i]->model,
                 (parr)[i]->size,
                 (parr)[i]->screen,
                 (parr)[i]->price);
     }

}



// cmp in qsort
int cmpphone(const void *a,const void *b){
     phone *za = *(phone **)a;
     phone *zb = *(phone **)b;
     return strcmp(za->model,zb->model);
}
void freearr(phone ***parr,int num){
     long long  i ;

     for (i = 0; i < (num); i++)
          free((*parr)[i]);

     free(*parr);
     *parr = NULL;
}
