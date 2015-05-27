#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <time.h>
#include "sort.h"
//#define timerun(time,mgr) printf("\n\t\t Time run of %s :  %lf\n",(mgr),(double)(time)/CLOCKS_PER_SEC)

typedef struct contact${
     char name[50];
     char tel[20];
     char email[60];
} contact;

#define DAT1 "p1.dat"
#define DAT2 "p2.dat"
#define DAT "p.dat"


int sizefile(FILE *f);
void readff(FILE *f,FILE *f2,contact ***parr,int *num);

int cmpcontact(const void *a,const void *b);
void printarr(contact **parr,int num);
void export(contact **parr,int num,FILE *f);
void freearr(contact ***parr,int num);

void mfflush() {
     int ch;
     while((ch = getchar()) && ch != '\n' && ch != EOF);
}

int main(){
     contact **s;
     int num;

     FILE *fi,
          *fi2,
          *fo;

     if((fi = fopen(DAT1,"rb+")) == NULL) {
          fprintf(stderr,"Can't read %s file !!\n",DAT1);
          exit(1);
     }
     if((fi2 = fopen(DAT2,"rb+")) == NULL) {
          fprintf(stderr,"Can't read %s file !!\n",DAT2);
          exit(1);
     }
     if((fo = fopen(DAT,"wb+")) == NULL) {
          fprintf(stderr,"Can't read %s file !!\n",DAT);
          exit(1);
     }


     readff(fi,fi2,&s,&num);
     printf("Number :%d\n",num);
     printarr(s,num);
     printf("\n\t\t\tStart sort\n");
/*
     // Insertion sort
     printf("\t\tInsertion Sort\n\n");
     insersort((void *)s,num,cmpcontact);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Quick sort
     printf("\t\tQuick Sort\n\n");
     readff(fi,&s,&num);
     quicksort((void *)s,0,num-1,cmpcontact);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");

     // Heap Sort
     printf("\t\tHeap Sort\n\n");
    // readff(fi,&s,&num);
     heapsort((void *)s,num,cmpcontact);
     printarr(s,num);

     freearr(&s,num);
     printf("\n");
*/
     // Merge sort
     printf("\t\tMerge Sort\n\n");
//     readff(fi,&s,&num);
     mergesort((void *)s,0,num-1,cmpcontact);
     printarr(s,num);
     export(s,num,fo);
     freearr(&s,num);
     printf("\n");
/*
     // Shell sort
     printf("\t\tShell Sort\n\n");
     readff(fi,&s,&num);
     shellsort((void *)s,num,cmpcontact);
     printarr(s,num);
     freearr(&s,num);
     printf("\n");

     // Intro sort
     printf("\t\tIntro Sort\n\n");
     readff(fi,&s,&num);
     introsort((void *)s,num,cmpcontact);
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
void readff(FILE *f,FILE *f2,contact ***parr,int *num){
     int i;
     *num = sizefile(f)/sizeof(contact);
     int num2 = sizefile(f2)/sizeof(contact);

     *parr = (contact **)malloc(((*num)+num2)*sizeof(contact*));
     if(*parr == NULL) {
          fprintf(stderr,"ERROR IN %s:%d\n",__FILE__,__LINE__);
          exit(1);
     }
     for (i = 0; i < ((*num)+num2); i++) {
          (*parr)[i] = (contact *)malloc(sizeof(contact));
          if(((*parr)[i]) == NULL) {
               fprintf(stderr,"ERROR IN %s:%d\n",__FILE__,__LINE__);
               exit(1);
          }
     }

     for (i = 0; i < (*num); i++) {
          fread((*parr)[i],sizeof(contact),1,f);
     }
     rewind(f);
     for (i = (*num); i < ((*num)+num2) ; i++) {
          fread((*parr)[i],sizeof(contact),1,f2);
     }
     *num = *num + num2;
     rewind(f2);
  /* for (i = 0; i < (*num); i++) { */
  /*   printf("%-3d - %d - %-30s - %-15s\n",(*parr)[i].no,(*parr)[i].mssv,(*parr)[i].name,(*parr)[i].tel); */
  /* } */
}

void printarr(contact **parr,int num){
     int i;
     for (i = 0; i < num; i++) {
          printf("\t%-50s - %-20s - %-s \n",
                 (parr)[i]->name,
                 (parr)[i]->tel,
                 (parr)[i]->email);
     }

}
void export(contact **parr,int num,FILE *f){
     int i;
     int c = 0;
     for (i = 0; i < num; i++) {
          c+=fwrite(parr[i],sizeof(contact),1,f);
     }
     printf("\n\t\tExport complete with %d element\n",c);
}


// cmp in qsort
int cmpcontact(const void *a,const void *b){
     contact *za = *(contact **)a;
     contact *zb = *(contact **)b;
     return strcmp(za->name,zb->name);
}
void freearr(contact ***parr,int num){
     long long  i ;

     for (i = 0; i < (num); i++)
          free((*parr)[i]);

     free(*parr);
     *parr = NULL;
}
