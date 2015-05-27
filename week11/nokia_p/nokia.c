#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Ginz.h"
#include "BST.h"

typedef struct $phone{
  char model[40];
  int size;
  float screen;
  int price;
} phone;


#define TXT "nokiaDB.txt"
#define DAT "nokiaDB.dat"


int sizefile(FILE *f);
int cmpphone(const void *a,const void *b);
phone ** importfdat(FILE *f,int wop,int boe,int *num);
phone ** importftxt(FILE *f, int *num);
void ptree(tree t);
void exporttree(tree t,FILE *fout);
tree *searchphone(tree *t);
void modifyphone(tree *t);
void addphone(tree *t);
void deletephone(tree *t);


int main(){

     FILE* ftxt = fopen(TXT,"r")
     ,*fdat = fopen(DAT,"rb");

     if(ftxt == NULL) {
          fprintf(stderr,"\t\tERROR Can't not read %s\n ",TXT);
          exit(1);
     }

     if(fdat == NULL){
          fprintf(stderr,"\t\tERROR Can't not read %s\n ",DAT);
          exit(1);
     }

     tree *phonet = (tree*)malloc(sizeof(tree));
     if(phonet == NULL){
          fprintf(stderr,"\t\tERROR : Allocated failed %s:%d\n",__FILE__,__LINE__);
          exit(1);
     }

     MakeNullTree(phonet);
     phone** phonearr;
     int num = 0;
     tree *find;
     while(1){
          switch(getmenu("import;add;remove;Modify;search;show;Export",7,1)){
          case 1:if(*phonet != NULL ){
                    freetree(phonet);
               }
               if(getmenu("Import txt;Import Dat",2,0) == 1){
                    printf("\t\tImport from %s file\n",TXT);
                    phonearr = importftxt(ftxt,&num);
                    //printf("Number :%d\n",num);
                    addfarr(phonet,(void*)phonearr,0,num-1,cmpphone);
                    printf("\t\tNumber of phone import to tree :%d\n",nb_nodes(*phonet));
               } else {
                    printf("\t\tImport from %s file\n",DAT);
                    phonearr = importfdat(fdat,1,0,&num);
                    //printf("Number :%d\n",num);
                    addfarr(phonet,(void *)phonearr,0,num-1,cmpphone);
                    printf("\t\tNumber of phone import to tree :%d\n",nb_nodes(*phonet));
               }
               break;

          case 2:
               if(*phonet == NULL){
                    printf("\t\t\t  Please import first !!  \n");
               } else {
                    addphone(phonet);
               }
               break;
          case 3:
               if(*phonet == NULL){
                    printf("\t\t\t  Please import first !!  \n");
               } else {
                    deletephone(phonet);
               }
               break;

          case 4:
               if(*phonet == NULL){
                    printf("\t\t\t  Please import first !!  \n");
               } else {
                    modifyphone(phonet);
               }
               break;
          case 5:
               if(*phonet == NULL){
                    printf("\t\t\t  Please import first !!  \n");
               } else {
                   find =  searchphone(phonet);
                   if(find ){
                        printf("\t\t Found Key on tree\n");
                   }
               }
               break;
          case 6:if(*phonet == NULL){
                    printf("\t\t\t  Please import first !!  \n");
               } else {
                    in_order(*phonet,ptree);
               }
               break;
          case 7:if(*phonet == NULL){
                    printf("\t\t\t  Please import first !!  \n");
               } else {
                    fclose(fdat);
                    remove(DAT);
                    fdat = fopen(DAT,"wb+");
                    if(fdat == NULL){
                         fprintf(stderr,"\t\tERROR :Can't write file %s\n",DAT);
                         exit(1);
                    }
                    exporttree(*phonet,fdat);
               }
               break;
          case 0:
               printf("\t\tExit Program !!\n");
               if(*phonet != NULL){
                    freetree(phonet);
                    free(phonearr);
                    free(phonet);
               }
               fclose(ftxt);
               fclose(fdat);
               goto end;
          }
     }
end:
     return  0;
}

// size of file
int sizefile(FILE *f){
  int prev = ftell(f);
  fseek(f,(long)0,SEEK_END);
  int size = ftell(f);
  fseek(f,prev,SEEK_SET);
  return size;
}


// import from dat file
phone ** importfdat(FILE *f,int wop,int boe,int *num){

     phone **parr;
     // wop = part(2) or whole(1)
     // boe = end(2) or begin(1)

     int e,offset,i;*num = sizefile(f)/sizeof(phone);
     if(wop == 1)   {// whole
          //
          parr = (phone **)malloc(sizeof(phone*)*(*num));
          if(parr == NULL){
               fprintf(stderr,"\t\tERROR allocated failed %s:%d\n",__FILE__,__LINE__);
               exit(1);
          }

          for (i = 0; i < (*num); i++) {
               parr[i] = (phone *)malloc(sizeof(phone));
               if(parr[i] == NULL){
                    fprintf(stderr,"\t\tERROR allocated failed %s:%d\n",__FILE__,__LINE__);
                    exit(1);
               }
          }
          //
          for (i = 0; i < (*num); i++) {
               fread(parr[i],sizeof(phone),1,f);
          }
          rewind(f);

          return parr;

     }  else {

          if(boe == 1){ //part begin
               do {
                    printf("\t\tInput offset(<%d) : ",*num);scanf("%d",&offset);mfflush();
                    if(offset < 0 ||  offset > *num ) printf("\t\tWrong input value !!\n input again \n");
               } while (offset < 0 ||  offset > *num);

               do {
                    printf("\t\tInput element want to read (<%d) : ",(*num)-offset);scanf("%d",&e);mfflush();
                    if(e < 0 ||  e > (*num)-offset ) printf("\t\tWrong input value !!\n input again \n");
               } while (e < 0 ||  e > (*num)-offset);
               //
               parr = (phone **)malloc(sizeof(phone)*e);
               if(parr == NULL){
                    fprintf(stderr,"\t\tERROR allocated failed %s:%d\n",__FILE__,__LINE__);
                    exit(1);
               }

               for (i = 0; i < (e); i++) {
                    parr[i] = (phone *)malloc(sizeof(phone));
                    if(parr[i] == NULL){
                         fprintf(stderr,"\t\tERROR allocated failed %s:%d\n",__FILE__,__LINE__);
                         exit(1);
                    }
               }
               //
               if(offset != 0)  fseek(f,sizeof(phone)*(offset-1),SEEK_SET);

               for (i = 0; i < (e); i++) {
                    fread(parr[i],sizeof(phone),1,f);
               }
               rewind(f);
               *num = e;
               return parr;

          } else {//part end
               do {
                    printf("\t\tInput offset(<%d) : ",*num);scanf("%d",&offset);mfflush();
                    if(offset < 1 ||  offset > *num ) printf("\t\tWrong input value !!\n input again \n");
               } while (offset < 1 ||  offset > *num);

               do {
                    printf("\t\tInput element want to read (<%d) : ",*num-offset);scanf("%d",&e);mfflush();
                    if(e < 0 ||  e > *num-offset ) printf("\t\tWrong input value !!\n input again \n");
               } while (e < 0 ||  e > *num-offset);

               parr = (phone **)malloc(sizeof(phone*)*e);
               if(parr == NULL){
                    fprintf(stderr,"\t\tERROR allocated failed %s:%d\n",__FILE__,__LINE__);
                    exit(1);
               }

               for (i = 0; i < (e); i++) {
                    parr[i] = (phone *)malloc(sizeof(phone));
                    if(parr[i] == NULL){
                         fprintf(stderr,"\t\tERROR allocated failed %s:%d\n",__FILE__,__LINE__);
                         exit(1);
                    }
               }
               //


               fseek(f,(long)0,SEEK_END);
               fseek(f,-sizeof(phone)*offset,SEEK_CUR);

               for (i = 0; i < (e); i++) {
                    fread(parr[i],sizeof(phone),1,f);
                    fseek(f,-sizeof(phone)*2,SEEK_CUR);
               }
               rewind(f);
               *num = e;
               return parr;
               //// <----
          }
     }
}



// import from txt file
phone ** importftxt(FILE *f, int *num){
     phone **parr;
     int i,c = 0;
     char s[10000];

     // get line
     while ((fgets(s,10000,f)) != NULL) {
          c++;
     }

     rewind(f);

     parr = (phone**)malloc(sizeof(phone*)*c);
     if(parr == NULL){
          fprintf(stderr,"\t\tERROR in %s:%d\n",__FILE__,__LINE__);
          exit(1);
     }
     for (i = 0; i < c; i++) {
          parr[i] = (phone*)malloc(sizeof(phone));
          if(parr[i] == NULL){
               fprintf(stderr,"\t\tERROR in %s:%d\n",__FILE__,__LINE__);
               exit(1);
          }
     }

     for (i = 0; i < c; i++) {
          fscanf(f,"%[^|]|%d|%f|%d\n",parr[i]->model,&parr[i]->size,&parr[i]->screen,&parr[i]->price);
     }

     *num = c;

     return parr;
}


void ptree(tree t){
     if(t == NULL) return;
     phone *temp = t->element;
     printf("%-40s | %-3d gb | %-3.1f '' |%-10d VND\n",
            temp->model,
            temp->size,
            temp->screen,
            temp->price);
}

void exporttree(tree t,FILE *fout){
     if(t == NULL) return;
     phone *temp = t->element;
     fwrite(temp,sizeof(phone),1,fout);
     exporttree((t->left),fout);
     exporttree((t->right),fout);
}

tree *searchphone(tree *t){


     phone keyf;
find_key:
     printf("\t\t\tSearch By model : ");
     scanf("%[^\n]",keyf.model);mfflush();

     tree *found =search(t,&keyf,cmpphone);

     if(found == NULL){
          printf("\t\t\tModel %s not found \n",keyf.model);
          int c;
          printf("\t\t\tDo you want to continue search ?\n");
          if((c = getmenu("Yes;No",2,0)) == 1){
               goto find_key;
          }
          else return NULL;
     }


     return found;
}

void modifyphone(tree *t){


     tree *found = searchphone(t);
re_find:
     if(found == NULL){
          printf("\t\t\tYou have been cancelled search function\n");

          int c;
          printf("\t\t\tDo you want to continue modify you should continue search ?\n");
          if((c = getmenu("Yes;No",2,0)) == 1){
               goto re_find;
          }
          else return;
     }

     int c;
     printf("\t\t\tWhat you want to modify ?\n");
     if((c = getmenu("Model;Size;Screen size;Price",4,1)) == 1){
          printf("\t\tModel %s --> ?",((phone*)(*found)->element)->model);
          scanf("%[^\n]",((phone*)(*found)->element)->model);mfflush();
     } else if(c == 2) {
          printf("\t\tSize %d --> ?",((phone*)(*found)->element)->size);
          scanf("%d",&(((phone*)(*found)->element)->size));mfflush();
     } else if(c== 3){
          printf("\t\tSreen size %.2f --> ?",((phone*)(*found)->element)->screen);
          scanf("%f",&(((phone*)(*found)->element)->screen));mfflush();
     } else if(c == 4){
          printf("\t\tPrice %d --> ?",((phone*)(*found)->element)->price);
          scanf("%d",&(((phone*)(*found)->element)->price));mfflush();
     } else if (c == 0){
          goto end;
     }
end:
     return;
}

void addphone(tree *t){
     phone *new = (phone *)malloc(sizeof(phone));
     if(new == NULL){
          fprintf(stderr,"\t\tERROR :Allocate failed %s:%d\n",__FILE__,__LINE__);
          exit(1);
     }
all:
     printf("\t\tPhone Model : ");scanf("%[^\n]",new->model);mfflush();

     printf("\t\tPhone size : ");scanf("%d",&(new->size));mfflush();

     printf("\t\tPhone sreen size : ");scanf("%f",&(new->screen));mfflush();

     printf("\t\tPhone price : ");scanf("%d",&(new->price));mfflush();
check:
     printf("\t\tYou have create phone has detail : %s %d GB %.2f '' %d VND\n",new->model,new->size,new->screen,new->price);

     printf("\t\tDo you want to confirm it ?\n");
     int c;
     if((c = getmenu("Yes;No and go to edit",2,0)) == 2){
          int cc;
          printf("\t\tWhat you want to edit\n");
          if((cc =getmenu("All;Model;size;screen;price",5,0)) == 1){
               goto all;
          } else if(cc == 2){
               printf("\t\tPhone Model : ");scanf("%[^\n]",new->model);mfflush();
               goto check;
          } else if(cc == 3){
               printf("\t\tPhone size : ");scanf("%d",&(new->size));mfflush();
               goto check;
          } else if(cc == 4){
               printf("\t\tPhone sreen size : ");scanf("%f",&(new->screen));mfflush();
               goto check;
          } else if (cc == 5){
               printf("\t\tPhone price : ");scanf("%d",&(new->price));mfflush();
               goto check;
          }
     } else{
          insert(t,new,cmpphone);
          goto end;
     }
end:
     return ;
}

void deletephone(tree *t){


     tree *found = searchphone(t);
re_find:
     if(found == NULL){
          printf("\t\t\tYou have been cancelled search function\n");

          int c;
          printf("\t\t\tDo you want to continue modify you should continue search ?\n");
          if((c = getmenu("Yes;No",2,0)) == 1){
               goto re_find;
          }
          else return;
     }
     printf("\t\tYou have find phone has detail : %s %d %.2f %d \n",((phone*)(*found)->element)->model,
            ((phone*)(*found)->element)->size,((phone*)(*found)->element)->screen,((phone*)(*found)->element)->price);

     printf("\t\tDo you want to delete it\n");
     int c;
     if((c = getmenu("Yes;No",2,0)) == 1){
          deletemin(t,(*found)->element,cmpphone);
     } else return ;
}


int cmpphone(const void *a,const void *b){
     phone *za = *(phone **)a;
     phone *zb = *(phone **)b;
     return strcmp(za->model,zb->model);
}
