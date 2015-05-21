#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE 20
typedef struct $phone{
  char model[40];
  int size;
  float screen;
  int price;

} phone;

typedef phone VARTYPE;

#include "Ginz.h"
#include "link.h"


#define TXT "nokiaDB.txt"
#define DAT "nokiaDB.dat"

int num;

int navi(int next,int prev);
void importftxt(FILE *f,FILE *fo);
void importfdat(FILE *f,int wop,int boe);
void printdat(node *r);
void importfA(VARTYPE *parr);
void exporttdat(FILE *f);
void search(node *r,int mode);
void modify();


node *root2 = NULL;



int sizefile(FILE *f);



int main(int argc, char *argv[])
{
  FILE *ft,*fd;

  while (1) {
    switch(getmenu("Import DB from NokiaDB.dat;Print data;Insert data;Delete data;Search Data & modify data;Devide list & Extract List;Reverse list;Save to file;Quit",9,0))
      {  mfflush();
      case 1:
        if((fd = fopen(DAT,"r+b")) == NULL) printf("\t\tCan't read file %s",DAT);
        else {
          if(getmenu("Insert Whole;Insert Part",2,0) == 1) {
              importfdat(fd,1,1);
          } else {
            if(getmenu("From Begin;From ending",2,0) == 1) importfdat(fd,2,1);
            else importfdat(fd,2,2);
          }
            printf("\t\tImport DB complete !!\n");
            fclose(fd);
        } break;
      case 2:if(root == NULL && root2 == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          if(root2 == NULL) printdat(root);
          else {
            int c ;
            if((c = getmenu("Print data of first list;Print data of second list",2,0)) == 1)
              printdat(root); else printdat(root2);
          }
        }
        break;
      case 3:if(root == NULL){
          indent(2); printf("Import data first !!\n");
        } else {
          int c;
          VARTYPE p;
          printf("\t\tModel of phone :");scanf("%[^\n]",p.model);mfflush();
          printf("\t\tSize of phone :");scanf("%d",&p.size);mfflush();
          printf("\t\tPhone's size of screen :");scanf("%f",&p.screen);mfflush();
          printf("\t\tPhone's price :");scanf("%d",&p.price);mfflush();
          if((c = getmenu("Insert at Begining;Insert at Ending;Insert at Position",3,0)) == 1) {
            insertB(p);
          } else if (c == 2) insertE(p);
          else {
            int z;
            node *g;
            do {
            printf("\t\t Where you want to insert (if you don't want to insert anymore input -1 !! 1st = 0 postion) :");scanf("%d",&z);mfflush();
            g = insertAtPosition(p,z);
            } while (g == NULL && z != -1);
          }
        }break;
      case 4:if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          int c;
          if((c = getmenu("Delete at Postion;Delete current;Delete first",3,0))==1)  {
            int p;
            printf("\t\t Where you want to delelte (if you don't want to insert anymore input -1 !! 1st = 0 postion) :");scanf("%d",&p);mfflush();
            deleteAtPosition(p);
          } else if(c == 2) delNode(cur);
          else if(c == 3) delNode(root);
        } break;
      case 5:
        if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          int cc;
          if((cc = getmenu("Search data;Modify data",2,0)) == 1){
            int c;
            if((c = getmenu("Search By name;Search near match name;Search By Price",3,0)) ==1)
              search(root,1);
            else if(c == 2) search(root,3);
            else search(root,2);
          } else {
            modify();
          }
        } break;
      case 6:
        if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          int c;
          if((c = getmenu("Devide List;Extract list",2,0))==1){
            int p;
            printf("\t\tPostion you want to devide list : ");scanf("%d",&p);mfflush();
            root2 = devideList(root,last,p);
          } else {
            int p,n;
            printf("\t\tPostion you want to start extract list : ");scanf("%d",&p);mfflush();
            printf("\t\tLength of extract list : ");scanf("%d",&n);mfflush();
            extractList(p,n);
          }
        } break;
        case 7:if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          reversel();
        }break;
      case 8:if(root == NULL) {
          indent(2); printf("Import data first !!\n");
        } else {
          if((fd = fopen(DAT,"w+b")) == NULL) printf("Can't create file %s",DAT);
          else {
            exporttdat(fd);
          }
        }break;
      case 9:
        freelist(root);
        freelist(root2);
        indent(2);printf("Exit Program !!\n");
        return 0;
      }
  }
}
// export to dat
void exporttdat(FILE *f){
  if(root == NULL) {
    printf("\t\tList hasn't created !!\n");
    return;
  }
  node *p = root;
  while (p != NULL) {
    fwrite(p,sizeof(phone),1,f);
    p = p ->next;
  }
  rewind(f);
}


// import from array
void importfA(phone *parr){
  int i;

  for (i = 0; i < num; i++) {
    insertE(*parr);
    parr++;
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

// import from txt file
void importftxt(FILE *f,FILE *fo){
  freelist(root);
  phone *parr;
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

  num = c;
  importfA(parr);
  free(parr);
}


// import from dat file
void importfdat(FILE *f,int wop,int boe){
  freelist(root);
  phone *parr;
  // wop = part(2) or whole(1)
  // boe = end(2) or begin(1)

  int e,offset,i;num = sizefile(f)/sizeof(phone);
  if(wop == 1)   {// whole

    parr = (phone *)malloc(sizeof(phone)*num);
    int z =fread(parr,sizeof(phone),num,f);
    //printf("%d\n",z);
    rewind(f);
    importfA(parr);
    free(parr);
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
      importfA(parr);
      free(parr);

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
      importfA(parr);
      free(parr);
    }
    num = e;
  }

}
// print data
void printdat(node *r){
  int i,c;
  node *p = r;
  num = countList(r);
  printf("\t\t Data :\n");
  if(num < 11 )
    for (i = 0; i < num; i++) {
      printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",i+1,p->element.model,p->element.size,p->element.screen,p->element.price);
      p = p ->next;
    } else {
    int cc,z = 0 ;

    for(;;){

      int k = PAGE + z*PAGE;
      k = (k < num)?k:num;
      printf("\t\t Page %d\n",z+1);
      for (i = z*PAGE; i < k; i++) {
        if(p == NULL) break;
        printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",i+1,p->element.model,p->element.size,p->element.screen,p->element.price);
        p = p ->next;

      }
      if(PAGE > num) return;
      if(z == 0) {if(navi(1,0)== 1) z++;else return ;}
      else if(z*PAGE + PAGE > num) {
        if(navi(0,1)==1) {
          z--;
          int j;
          for(j = 0 ; j  < PAGE ; j++) p = pevNode(r,p);
          for(j = 0 ; j  < PAGE ; j++) p = pevNode(r,p);
        }
        else return;
      }
      else {
        if((c=navi(1,1)) ==1 ) {
          z--;
          int j;
          for(j = 0 ; j  < PAGE ; j++) p = pevNode(r,p);
          for(j = 0 ; j  < PAGE ; j++) p = pevNode(r,p);
        }
        else if(c ==2) z++;
        else  return ;
      }
    }
  }
}
// pagecontrol
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

void search(node *r,int mode){
  int num = countList(r);
  if(root == NULL) {
    printf("\t\tList hasn't create !!\n");
    return;
  }
  if ( mode == 1){ // search model
    int i,c = 0;
    node *p = root;
    char s[100];
    printf("\t\tSearch by model :");scanf("%[^\n]",s);mfflush();


    for (i = 0; i < num; i++) {
      if(!strcmp(s,p->element.model)) c++;
    }
    if(c != 0){
      c = 0;
      p = root;
      printf("\t\tSearch result : \n");
      for (i = 0; i < num; i++) {
        if(!strcmp(s,p->element.model)) printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",c+1,p->element.model,p->element.size,p->element.screen,p->element.price);
        p = p ->next;
      }
    } else {
      printf("\t\tNot found !!\n");
    }
  } else if (mode == 3) { // near match model
    int i,c = 0,z = 0,sum = 0;
    char s[100];
    printf("\t\tSearch by model :");scanf("%[^\n]",s);mfflush();

    node *p = root;

    for (i = 0; i < num; i++) {
      if(nmstr(p->element.model,s) == 1) {
        c++;
      }
      p = p ->next;
    }
    if(c != 0){
      p = root;
      sum = c;
      i = 0;

      printf("\t\tSearch result : \n");
      for(;;){
        c = z*PAGE;

        int k = PAGE + z*PAGE;
        k = (k < sum)?k:sum;
        printf("\t\t Page %d\n",z+1);
        for (;c < k;) {
          if(p == NULL) break;
          if(nmstr(p->element.model,s) == 1) {
            printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",c+1,p->element.model,p->element.size,p->element.screen,p->element.price);
            c++;
          }
          p = p ->next;
        }

        if(PAGE > sum ) return ;
        if(z == 0) {
          if(navi(1,0)== 1) z++;
          else return ;
        } else if(z*PAGE + PAGE > sum) {
          if(navi(0,1)==1) {
            z--;
            int j = 0;
            while (j < PAGE*2 && j < k) {
              if(nmstr(p->element.model,s) == 1) j++;
              p = pevNode(root,p);
            }
          } else return;
        } else {
          if((c=navi(1,1)) ==1 ) {
            z--;
            int j = 0;
            while (j < PAGE*2 && j < k) {
              if(nmstr(p->element.model,s) == 1) j++;
              p = pevNode(root,p);
            }
          }
          else if(c ==2) z++;
          else  return ;
        }
      }
    } else {
      printf("\t\t Not Found !!\n");
    }
  }else if(mode == 2) { // search price
    int i,c = 0,z = 0,sum = 0;
    long d;
    printf("\t\tSearch product slow than price :");scanf("%ld",&d);mfflush();

    node *p = root;

    for (i = 0; i < num; i++) {
      if(p->element.price < d && p->element.price != -1) {
        c++;
      }
      p = p ->next;
    }
    if(c != 0 ){
      p = root;
      sum = c;
      i = 0;
      printf("Search result : \n");

      for(;;){
        c = z*PAGE;

        int k = PAGE + z*PAGE;
        k = (k < sum)?k:sum;
        printf("\t\t Page %d\n",z+1);
        for (;c < k;) {
          if(p == NULL) break;
          if(p->element.price < d && p->element.price != -1) {
            printf("%-3d %-40s | %-3d gb | %-3.1f '' |%-10d VND\n",c+1,p->element.model,p->element.size,p->element.screen,p->element.price);
            c++;
          }
          p = p ->next;
        }

        if(PAGE > sum ) return ;
        if(z == 0) {
          if(navi(1,0)== 1) z++;
          else return ;
        } else if(z*PAGE + PAGE > sum) {
          if(navi(0,1)==1) {
            z--;
            int j;
            for(j = 0 ; j  < PAGE*2 ;) {
              p = pevNode(root,p);
              if(p->element.price < d && p->element.price != -1 == 1) j++;
            }
          } else return;
        } else {
          if((c=navi(1,1)) ==1 ) {
            z--;
            int j;
            for(j = 0 ; j  < PAGE*2 ;) {
              p = pevNode(root,p);
              if(p->element.price < d && p->element.price != -1 == 1) j++;
            }
          }
          else if(c ==2) z++;
          else  return ;
        }
      }
    } else {
      printf("\t\t Not Found !! \n");
    }
  }
}

// modify data
void modify(){
  int p,c = 0;
  node *z;
  do {
  printf("\t\tWhat position want to modify (1st = 0 postion) : ");scanf("%d",&p);mfflush();
  if(p  < 0 || p > countList(root)-1) printf("\t\tInvaild location !!\nInput value again !! \n");
  } while(p  < 0 || p > countList(root)-1);
  if(p == 0) z = root;
  else { z = root->next;
    while(z != NULL){
      c++;
      if(c == p) break;
      z = z->next;
    }
  }
  printf("\t\tData of position %d :",p);
  printf("%s %d gb %.2f'' %d VND\n",z->element.model,z->element.size,z->element.screen,z->element.price);

  printf("\t\tWhat you want to modify :");
  if((c = getmenu("Model;Size;Size of screen;Price",4,0)) == 1){
    printf("\t\t %s --> ",z->element.model);scanf("%[^\n]",z->element.model);mfflush();
  } else if(c == 2 ){
    printf("\t\t %d --> ",z->element.size);scanf("%d",&z->element.size);mfflush();
  } else if (c == 3){
    printf("\t\t %f --> ",z->element.screen);scanf("%f",&z->element.screen);mfflush();
  } else{
    printf("\t\t %d --> ",z->element.price);scanf("%d",&z->element.price);mfflush();
  }
  printf("\t\tData of position %d after modifed :",p);
  printf("%s %d gb %.2f'' %d VND\n",z->element.model,z->element.size,z->element.screen,z->element.price);
}
