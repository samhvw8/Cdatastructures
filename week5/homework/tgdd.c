#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ginz.h"


#define TXT "nokiaDB.txt"
#define DAT "nokiaDB.dat"
typedef struct $phone{
  char model[40];
  int size;
  float screen;
  int price;

} phone;


phone *parr;

int num;
int navi(int next,int prev);
void importftxt(FILE *f,FILE *fo);
void importfdat(FILE *f,int wop,int boe);
void printdat();
void search();
int sizefile(FILE *f);



int main(int argc, char *argv[])
{
  FILE *ft,*fd;
  int c = 0;

    while (1) {
      switch(getmenu("Import DB from text;Import DB from DB;Print all data;Search by model;Exit",5,0))
        {  mfflush();
        case 1:
          if((ft = fopen(TXT,"r")) == NULL) printf("\t\tCan't open file %s",TXT);
          else if((fd = fopen(DAT,"w+b")) == NULL) printf("Can't create file %s",DAT);
          else {
            importftxt(ft,fd);
            c = 1;
            fclose(ft);
            fclose(fd);
            printf("\t\tImport DB complete !!\n");
          } break;
        case 2:
          if((fd = fopen(DAT,"r+b")) == NULL) printf("\t\tCan't read file %s",DAT);
          else {
            if(getmenu("Insert Whole;Insert Part",2,0) == 1) {
              importfdat(fd,1,1);
            } else {
              if(getmenu("From Begin;From ending",2,0) == 1) importfdat(fd,2,1);
              else importfdat(fd,2,2);
            }
            c = 1;
            printf("\t\tImport DB complete !!\n");
            fclose(fd);
          } break;
        case 3:if(c == 0) {
            indent(2); printf("Import data first !!\n");
          } else {
            printdat();
          }  break;
        case 4:if(c == 0) {
            indent(2); printf("Import data first !!\n");
          } else {
            search();
          }break;
        case 5:
          indent(2);printf("Exit Program !!\n");
          return 0;
        }
    }
}
// size of file
int sizefile(FILE *f){
  int prev = ftell(f);
  fseek(f,(long)0,SEEK_END);
  int size = ftell(f);
  fseek(f,prev,SEEK_SET);
  return size;
}

// import from txt
void importftxt(FILE *f,FILE *fo){

  int i,c = 0;
  char s[10000];
  while ((fgets(s,10000,f)) != NULL) {
    c++;
  }
  rewind(f);

  parr = (phone *)malloc(sizeof(phone)*c);

  for (i = 0; i < c; i++) {
    fscanf(f,"%[^|]|%d|%f|%d\n",parr[i].model,&parr[i].size,&parr[i].screen,&parr[i].price);
  }

  fwrite(parr,sizeof(phone),c,fo);

  num = c;
}

void importfdat(FILE *f,int wop,int boe){
  // wop = part(2) or whole(1)
  // boe = end(2) or begin(1)

  int e,offset,i;num = sizefile(f)/sizeof(phone);

  if(parr != NULL) free(parr);

  if(wop == 1)   {// whole

    parr = (phone *)malloc(sizeof(phone)*num);
    int z =fread(parr,sizeof(phone),num,f);
    //printf("%d\n",z);
    rewind(f);
  }  else {

    if(boe == 1){ //part begin
      do {
        printf("\t\tInput offset(<%d) : ",num);scanf("%d",&offset);mfflush();
        if(offset < 0 ||  offset > num ) printf("\t\tWrong input value !!\n input again \n");
      } while (offset < 0 ||  offset > num);

      do {
        printf("\t\tInput element want to read (<%d) : ",num-offset);scanf("%d",&e);mfflush();
        if(e < 0 ||  e > num-offset ) printf("\t\tWrong input value !!\n input again \n");
      } while (e < 0 ||  e > num-offset);

      parr = (phone *)malloc(sizeof(phone)*e);

      if(offset != 0)  fseek(f,sizeof(phone)*(offset-1),SEEK_SET);

      fread(parr,sizeof(phone),e,f);
      rewind(f);

    } else {//part end
      do {
        printf("\t\tInput offset(<%d) : ",num);scanf("%d",&offset);mfflush();
        if(offset < 1 ||  offset > num ) printf("\t\tWrong input value !!\n input again \n");
      } while (offset < 1 ||  offset > num);

      do {
        printf("\t\tInput element want to read (<%d) : ",num-offset);scanf("%d",&e);mfflush();
        if(e < 0 ||  e > num-offset ) printf("\t\tWrong input value !!\n input again \n");
      } while (e < 0 ||  e > num-offset);

      parr = (phone *)malloc(sizeof(phone)*e);

      fseek(f,(long)0,SEEK_END);
      fseek(f,-sizeof(phone)*offset,SEEK_CUR);
      for (i = 0; i < e; i++) {
        fread(&parr[i],sizeof(phone),1,f);
        fseek(f,-sizeof(phone)*2,SEEK_CUR);
        //printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",i+1,parr[i].model,parr[i].size,parr[i].screen,parr[i].price);
      }
      rewind(f);
    }
    num = e;
  }

}
void printdat(){
  int i,c;

  printf("\t\t Data :\n");
  if(num < 11 )
    for (i = 0; i < num; i++) {
      printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",i+1,parr[i].model,parr[i].size,parr[i].screen,parr[i].price);
    } else {
    int cc,z = 0 ;

    for(;;){
      int k = 20 + z*20;
      k = (k < num)?k:num;
      printf("\t\t Page %d\n",z+1);
      for (i = z*20; i < k; i++) {
        printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",i+1,parr[i].model,parr[i].size,parr[i].screen,parr[i].price);
      }
      if(z == 0) {if(navi(1,0)== 1) z++;else return ;}
      else if(z*20 + 20 > num) {if(navi(0,1)==1) z--;else return;}
      else {
        if((c=navi(1,1)) ==1 ) z--;
        else if(c ==2) z++;
        else return;
      }

    }
  }
}

int navi(int next,int prev){
  char c,input[1000];
  int option,z,i;
  z = 0;
  printf("\n\t\t\t\tPage control \n");
  if(next  == 1 && prev == 1) {printf("\t\t 1.Prev 2.Next 3.Return menu\n\t\t Your choice : ");z = 4;}
  if(next  == 1 && prev == 0) {printf("\t\t 1.Next 2.Return menu\n\t\t Your choice : ");z = 3;}
  if(next  == 0 && prev == 1) {printf("\t\t 1.Prev 2.Return menu\n\t\t Your choice : "); z = 3;}
  do {
    i = 0;
    while((c=getchar())!= '\n') { input[i] = c; i++;} input[i]='\0';i++;
    if(checkan(input,i)) option = atoi(input);
    if(!checkan(input,i) || option > z || option < 0 ) printf("\t\tWrong input !!\n\t\tInput again : ");
  } while (!checkan(input,i) || option > z || option < 0 );
   return option;
}



void search(){
  int i;
  char s[100];
  printf("\t\tSearch by model :");scanf("%[^\n]",s);
  printf("Search result : ");
  for (i = 0; i < num; i++) {
    if(!strcmp(s,parr[i].model)) printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",i+1,parr[i].model,parr[i].size,parr[i].screen,parr[i].price);
  }
}
