#include <stdio.h>
#define MAX 10
typedef struct {
  int stt;
  long mssv;
  char ten[30];
  char [12];
  int diem;
} student;

void docfile(FILE *fp1);
void ghidiem();
void ghifile();

student hocsinh[MAX];

int main(int argc, char *argv[])
{
  FILE *fp1,*fp2;
  char filename1[]="danhsachlop.txt";
  char filename2[]="bangdiem.txt";

  if((fp1=fopen(filename1,"r"))==NULL) printf("Cannot open %s.\n",filename1);
  else {
    fp2=fopen(filename2,"w");


    fclose(fp1);
    fclose(fp2);
  }

  return 0;
}

void docfile(FILE *fp1){

}
