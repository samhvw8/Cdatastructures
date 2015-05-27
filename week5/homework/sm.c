#include <stdio.h>
#include <stdlib.h>
#define Finput "phonecontact.dat"
typedef struct ${
     char name[50];
     char tel[20];
     char email[60];
} Pcontact;


void spilit(FILE *fi,FILE *fo1,FILE *fo2,int offset);
void merge(FILE *fi1,FILE *fi2,FILE *fo);
int size(FILE *fi);




int main(int argc, char *argv[])
{
  if(argc <=4) printf("Wrong format !! \n USE : For spilit ./sm -s <FILE INPUT> <OFFSET> <FILE OUTPUT 1> <FILE OUTPUT 2> \nFOR MERGE ./sm -m <FILE INPUT 1> <FILE INPUT 2> <OUTPUT> \n");
  else {
    if(argc == 5) { // merge
      if(argv[1][1] != 'm') printf("Wrong input option !!\n");
      else {
        FILE *fi,*fi2;
        FILE *fo;
        if((fi = fopen(argv[2],"r")) == NULL) printf("Can't read %s file\n",argv[2]);
        else {
          if((fi2 = fopen(argv[3],"r")) == NULL) printf("Can't read %s file\n",argv[3]);
          else {
            if((fo = fopen(argv[4],"w")) == NULL) printf("Can't create %s file\n",argv[4]);
            else {
              merge(fi,fi2,fo);
              fclose(fi);
              fclose(fi2);
              fclose(fo);
            }
          }
        }
      }
    }
    if(argc == 6){ // spilit
      if(argv[1][1] != 's') printf("Wrong input option !!\n");
      else {
        FILE *fi;
        FILE *fo,*fo2;

        if((fi = fopen(argv[2],"r")) == NULL) printf("Can't read %s file\n",argv[2]);
        else {
          if((fo = fopen(argv[4],"w")) == NULL) printf("Can't create %s file\n",argv[3]);
          else {
            if((fo2 = fopen(argv[5],"w")) == NULL) printf("Can't create %s file\n",argv[4]);
            else {

              spilit(fi,fo,fo2,atoi(argv[3]));
              fclose(fi);
              fclose(fo2);
              fclose(fo);
            }
          }
        }
      }
    }
  }
  return 0;
}



void spilit(FILE *fi,FILE *fo1,FILE *fo2,int offset){
  Pcontact *Parr;
  int num = size(fi)/sizeof(Pcontact);
  int i;
  if(offset > num || offset < 0) {
    printf("Wrong input offset !!\n");
    return ;
  }

  Parr = (Pcontact *)malloc(sizeof(Pcontact)*num);

  fread(Parr,sizeof(Pcontact),num,fi);
  fwrite(Parr,sizeof(Pcontact),offset,fo1);

  for (i = offset; i < num; i++) {
    fwrite(&Parr[i],sizeof(Pcontact),1,fo2);

  }
  free(Parr);
}


void merge(FILE *fi1,FILE *fi2,FILE *fo){
  Pcontact *Parr;

  int i;

  Parr = (Pcontact *)malloc(size(fi1));
  int n = fread(Parr,1,size(fi1),fi1);
  fwrite(Parr,1,n,fo);
  free(Parr);

  Parr = (Pcontact *)malloc(size(fi2));
  int n1 = fread(Parr,1,size(fi2),fi2);
  fwrite(Parr,1,n1,fo);
  free(Parr);
}




int size(FILE *fi){
  //  int e = 0;
  int prev = ftell(fi);

  fseek(fi,(long)0,SEEK_END);
  int size = ftell(fi);
  fseek(fi,(long)0,SEEK_SET);
  return size;
}
