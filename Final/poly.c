#include "Ginz.h"
#include "dlink.h"


#define FILENAME "poly.txt"


typedef struct {
  int coef;
  int exp;
} element;


void readff(FILE *f,llist *P,llist *Q);
void printdata(llist p);
void printexp(llist p);
void printexpadd(llist p);
void standardize(llist *p);
llist *add(llist *p,llist *q);

int main(){
  FILE *f;
  llist *P,*Q;
  P = (llist *)malloc(sizeof(llist));
  if(P == NULL) {
    fprintf(stderr,"ERROR : Allocated memory failed !!\n");
    exit(1);
  }
  Q = (llist *)malloc(sizeof(llist));
  if(Q == NULL) {
    fprintf(stderr,"ERROR : Allocated memory failed !!\n");
    exit(1);
  }
  linit(P);
  linit(Q);
  f = fopen(FILENAME,"r");
  if(f == NULL ) {
    fprintf(stderr,"ERROR : can't read file %s",FILENAME);
    exit(1);
  }

 
  int c = 0;

  for(;;){
    switch(getmenu("Read data from file;Display expression;Standardize;Add Poly;Quit",5,0)){
    case 1:
      c++;
      readff(f,P,Q);
      printf("\t\t Read data complete !!\n");
      printf("\t\tData \n\t\t\t");
      printdata(*P);
      printf("\t\t\t");
      printdata(*Q);
      break;
    case 2:
      if(c == 0 )printf("Input data first !!\n");
      else{
	
	  printf("P expression :");
	  printexp(*P);
	  printf("Q expression :");
	  printexp(*Q);
	
	  printf("P expression :");
	  printexpadd(*P);
	  printf("Q expression :");
	  printexpadd(*Q);
	
      }
      break;
    case 3:
      if(c == 0 )printf("Input data first !!\n");
      else {
	standardize(P);
	standardize(Q);
	printf("\t\tStandardize Complete !!\n");
        printf("P expression :");
        printexp(*P);
        printf("Q expression :");
        printexp(*Q);
	
      }break;
    case 4:
      if(c == 0 )printf("Input data first !!\n");
      else {
           llist *R = add(P,Q);	
           printf("sum pression :");
           printexp(*R);
           freelist(R->r);
           free(R);
      }break;
    case 5: 
      freelist(P->r);
      free(P);
      freelist(Q->r);
      free(Q);
      fclose(f);
      printf("\t\tFree List compelete && Exit program !!\n");
      return 0;
    }
    
  
  }





  return 0;

}

void readff(FILE *f,llist *P,llist *Q){
  
  while(1){
    int c;
    fscanf(f,"%d",&c);
    if(c != -1){
      element *num;
      num = (element *)malloc(sizeof(element));
      if(num == NULL) {
	fprintf(stderr,"ERROR : Allocated memory failed !!\n");
	exit(1);
      }
      num->coef = c;
      fscanf(f,"%d",&(num->exp));     
      insertE(P,num);
    } else {
      char check;
      fscanf(f,"%c",&check);
      if(check == '\n') goto nextloop;
      else {
      element *num;
      num = (element *)malloc(sizeof(element));
      if(num == NULL) {
	fprintf(stderr,"ERROR : Allocated memory failed !!\n");
	exit(1);
      }
      num->coef = c;
      fscanf(f,"%d",&(num->exp));     
      insertE(P,num);
      }
    }
  }
 nextloop:

 while(1){
    int c;
    fscanf(f,"%d",&c);
    if(c != -1){
      element *num;
      num = (element *)malloc(sizeof(element));
      if(num == NULL) {
	fprintf(stderr,"ERROR : Allocated memory failed !!\n");
	exit(1);
      }
      num->coef = c;
      fscanf(f,"%d",&(num->exp));     
      insertE(Q,num);
    } else {
      char check;
      fscanf(f,"%c",&check);
      if(check != ' ') goto end;
      else {
	element *num;
	num = (element *)malloc(sizeof(element));
	if(num == NULL) {
	  fprintf(stderr,"ERROR : Allocated memory failed !!\n");
	  exit(1);
	}
	num->coef = c;
	fscanf(f,"%d",&(num->exp));     
	insertE(Q,num);
      }
    }
  }

 end:

 return ;
}


void printexp(llist p){
  node *z = p.r;
  while(z != NULL){
    element *a = (element*)z->v; 
    if(a->exp != 0 && a->coef != 0)    printf("%dx^%d + ",a->coef,a->exp); 
    else if(a->exp == 0 && a->coef != 0) printf("%d",a->coef); 
    z = z->next;
  }
  printf("\n");

}
void printdata(llist p){
     node *z = p.r;
     while(z != NULL){
          element *a = (element*)z->v; 
          printf("%d %d ",a->coef,a->exp); 
          z = z->next;
     }
     printf("\n");

}

void printexpadd(llist p){
  node *z = p.r;
  while(z != NULL){
    element *a = (element*)z->v; 
    if(a->exp != 0 && a->coef != 0)    printf("%dx^%d(%p) + ",a->coef,a->exp,z); 
    else if(a->exp == 0 && a->coef != 0) printf("%d(%p) + ",a->coef,z); 
    z = z->next;
  }
  printf("\n");

}
void standardize(llist *p){
  int maxexp = 0;

  node *z = p->r;
  while(z != NULL){
    element *a = (element*)z->v; 
    if(a->exp > maxexp ) maxexp = a->exp; 
    z = z->next;
  }
  
  int *arr = (int *)malloc(sizeof(int)*(maxexp+1));
  if(arr == NULL)  {
    fprintf(stderr,"ERROR : Allocated memory failed !!\n");
    exit(1);
  }
  int i;
  for(i = 0;i<maxexp+1;i++)arr[i] = 0;
  z = p->r;
  while(z != NULL){
    element *a = (element*)z->v; 
    arr[a->exp] += a->coef;
    z = z->next;
  }
  
  freelist(p->r);
  p->r = NULL;
  for(i = maxexp;i>= 0;i--) {
    element *num;
    num = (element *)malloc(sizeof(element));
    if(num == NULL) {
      fprintf(stderr,"ERROR : Allocated memory failed !!\n");
      exit(1);
    }
    num->exp = i;
    num->coef = arr[i];
    insertE(p,num);
  }
  free(arr);

  
}

llist *add(llist *p,llist *q){

  int maxexp = 0;

  node *z = p->r;
  while(z != NULL){
    element *a = (element*)z->v; 
    if(a->exp > maxexp ) maxexp = a->exp; 
    z = z->next;
  }
  z = q->r;
    while(z != NULL){
      element *a = (element*)z->v; 
      if(a->exp > maxexp ) maxexp = a->exp; 
      z = z->next;
  }
  
  int *arr = (int *)malloc(sizeof(int)*(maxexp+1));
  if(arr == NULL)  {
    fprintf(stderr,"ERROR : Allocated memory failed !!\n");
    exit(1);
  }
  int i;
  for(i = 0;i<maxexp+1;i++)arr[i] = 0;
  z = p->r;
  while(z != NULL){
    element *a = (element*)z->v; 
    arr[a->exp] += a->coef;
    z = z->next;
  }
  z = q->r;
  while(z != NULL){
    element *a = (element*)z->v; 
    arr[a->exp] += a->coef;
    z = z->next;
  }
  
  llist *out = (llist *)malloc(sizeof(llist));
  if(out == NULL) {
       fprintf(stderr,"ERROR : Allocated memory failed !!\n");
       exit(1);
  }
  linit(out);
  for(i = maxexp;i>= 0;i--) {
    element *num;
    num = (element *)malloc(sizeof(element));
    if(num == NULL) {
      fprintf(stderr,"ERROR : Allocated memory failed !!\n");
      exit(1);
    }
    num->exp = i;
    num->coef = arr[i];
    insertE(out,num);
  }

  free(arr);
  return out;

}
