#include <stdio.h>
#include <string.h>
#define MAX_LEN 81

void compare(FILE *f1,FILE *f2);

int main(int argc, char *argv[])
{
  FILE *fp1,*fp2;
  char filename1[100];
  char filename2[100];

  if (argc != 3) {printf("Wrong command.\n"); return 0;}
  strcpy(filename1,argv[1]);
  strcpy(filename2,argv[2]);

  if ((fp1=fopen(filename1,"r"))== NULL) printf("Cannot open %s.\n",filename1);
  else if ((fp2=fopen(filename2,"r"))== NULL) printf("Cannot open %s.\n",filename2);
  else {
    compare(fp1,fp2);
    fclose(fp1);
    fclose(fp2);
  }

  return 0;
}

void compare(FILE *f1,FILE *f2){
  char s1[MAX_LEN];
  char s2[MAX_LEN];
  int line=0;

  do {
      line++;
      if(strcmp(s1,s2)!=0) printf("%d\n",line);
    while ((fgets(s1,MAX_LEN,f1))==NULL && (fgets(s2,MAX_LEN,f2))!=NULL){
      line++;
      printf("%d\n",line);
    }
    while ((fgets(s1,MAX_LEN,f1))!=NULL && (fgets(s2,MAX_LEN,f2))==NULL){
      line++;
      printf("%d\n",line);
    }
  } while ((fgets(s1,MAX_LEN,f1))!=NULL && (fgets(s2,MAX_LEN,f2))!=NULL);
  line++;
  printf("%d\n",line);
}
