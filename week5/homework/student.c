#include <stdio.h>
#include <stdlib.h>
#define OUT "grade.dat"
typedef struct ${
  int no,
    mssv;
  char name[30];
  char tel[15];
  int grade ;
} student;

void gfiletodata(FILE *fi,FILE *fo);
void readff(FILE *f);
int sizefile(FILE *f);


int main(int argc, char *argv[]){

  if(argc != 2) printf("Wrong Input !! \n USAGE :./student <INPUT FILE>\n");
  else {
    FILE *fi,*fo;
    if((fi = fopen(argv[1],"r")) == NULL) printf("Can't read %s file !!\n",argv[1]);
    else{
      if((fo = fopen(OUT,"w+b")) == NULL) printf("Can't create %s file !!\n",OUT);
      else {

        gfiletodata(fi,fo);
        readff(fo);

        fclose(fi);
        fclose(fo);
      }
    }
  }

  return 0;
}
void readff(FILE *f){
  int i,num = sizefile(f)/sizeof(student);
  student *sarr;

  sarr = (student *)malloc(num*sizeof(student));
  rewind(f);
  fread(sarr,sizeof(student),num,f);
  printf("\nGrade :\n");
  for (i = 0; i < num; i++) {
    printf("%d - %d - %-30s - %-15s - %d\n",sarr[i].no,sarr[i].mssv,sarr[i].name,sarr[i].tel,sarr[i].grade);
  }

}
void gfiletodata(FILE *fi,FILE *fo){

  char buff[10000];
  int i,c = 0;
  student *Spt;
  while ((fgets(buff,10000,fi)) != NULL) {
    c++;
  }
  rewind(fi);
  Spt = (student *)malloc(sizeof(student)*c);
  for (i = 0; i < c; i++){

    fscanf(fi,"%d-%d-%[^-]-%[^-]-%d\n",&Spt[i].no,&Spt[i].mssv,Spt[i].name,Spt[i].tel,&Spt[i].grade);
    //printf("%d-%d-%s-%s-%d\n",Spt[i].no,Spt[i].mssv,Spt[i].name,Spt[i].tel,Spt[i].grade);
  }
  fwrite(Spt,sizeof(student),c,fo);

  free(Spt);
}

int sizefile(FILE *f){
  int prev = ftell(f);
  fseek(f,(long)0,SEEK_END);
  int size = ftell(f);
  fseek(f,prev,SEEK_SET);
  return size;
}
