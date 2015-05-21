#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"


char file1[100],file2[100];

void mfflush() {
  int ch;
  while((ch = getchar()) && ch != '\n' && ch != EOF);
}

int main(int argc, char *argv[]){
  student *s,*s2;
  int num,num2;
  if(argc != 3) printf("Wrong Input !! \n"
                       " USAGE :./student <INPUT FILE 1> <INPUT FILE 2>  \n");
  else {
    FILE *fi,*fi2;
    if((fi = fopen(argv[1],"r+")) == NULL) {
      fprintf(stderr,"Can't read %s file !!\n",argv[1]);
      exit(1);
    }
    else{
      if((fi2 = fopen(argv[2],"r+")) == NULL) {
        fprintf(stderr,"Can't read %s file !!\n",argv[2]);
        exit(1);
      }
      else {
        strcpy(file1,argv[1]);
        strcpy(file2,argv[2]);
        // printf("\n\t\t Read list 1 :\n");
        readff(fi,&s,&num);
        // printf("\n\t\t Read list 2 :\n");
        readff(fi2,&s2,&num2);
        diff(s,s2,num,num2);
        fclose(fi);
        fclose(fi2);
        free(s);
        free(s2);
      }
    }
  }
  return 0;
}
void diff(student *a,student *b,int num,int num2){
  int i,f;
  int mark[num2];
  printf("\n\t\t Student in file %s not in %s is :\n",file1,file2);
  //
  for (i = 0; i < num2; i++) mark[i] = 0;
  //
  for (i = 0; i < num; i++) {
    if((f = rBinSearch(b,a[i].name,0,num2-1)) != -1){
      mark[f] = 1;
    } else printf("%-3d - %d - %-30s - %-15s\n",a[i].no,a[i].mssv,a[i].name,a[i].tel);
  }

  printf("\n\t\t Student in file %s not in %s is :\n",file2,file1);

  for (i = 0; i < num2; i++) {
    if(mark[i] == 0) if((f = rBinSearch(a,b[i].name,0,num2-1)) == -1)  printf("%-3d - %d - %-30s - %-15s\n",b[i].no,b[i].mssv,b[i].name,b[i].tel);
  }

}
// binary search for student
int rBinSearch(student *L,char *Target,int Lo,int Hi){
  if(Hi == Lo)
    if(strcmp(L[Hi].name,Target) == 0) return Hi;
    else return -1;
  if(Lo > Hi) return -1;
  int Mid = (Lo + Hi)/2;
  int f = 0;
  if((f = strcmp(L[Mid].name,Target) ) == 0) return Mid;
  else if(f > 0) rBinSearch(L,Target,Lo,Mid - 1);
  else return rBinSearch(L,Target,Mid + 1,Hi);
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
void readff(FILE *f,student **sarr,int *num){
  int i;
  *num = sizefile(f);
  *sarr = (student *)malloc((*num)*sizeof(student));

  for (i = 0; i < (*num); i++) {
    (*sarr)[i].no = i;
    fscanf(f,"%d|%[^|]|%s[^\\]",&(*sarr)[i].mssv,(*sarr)[i].name,(*sarr)[i].tel);
  }

  qsortstudent(*sarr,num);

  /* for (i = 0; i < (*num); i++) { */
  /*   printf("%-3d - %d - %-30s - %-15s\n",(*sarr)[i].no,(*sarr)[i].mssv,(*sarr)[i].name,(*sarr)[i].tel); */
  /* } */
}
// cmp in qsort
int cmpDic(const void *a,const void *b){
  student za = *(student *)a
  ,zb = *(student *)b;
  return strcmp(za.name,zb.name);
}
// qsort for student
void qsortstudent(student *sarr,int *num){
  qsort(sarr,(*num),sizeof(student),cmpDic);
}

