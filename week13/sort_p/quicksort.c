#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define VARTYPE int

#define TIME(BEGIN,END) printf("Time sorting is %.6lf s\n",(double)(END - BEGIN)/CLOCKS_PER_SEC);

VARTYPE * readalist(FILE *s,int num);
void printlist(VARTYPE *arr,int num);


int partion(VARTYPE *A,int q,int r,int pivotI);
void quicksort(VARTYPE *A,int q,int r);
void swap(VARTYPE *a,VARTYPE *b);



int main(int argc, char const *argv[])
{
  clock_t begin,end;
  FILE *fp;
  VARTYPE *arr;
  int i,num;
  srand(time(NULL));
  if(argc != 3 && argc != 4) printf("%s\n","Wrong Input !!");
  else {
    if(!strcmp(argv[1],"y")) {
      printf("Creating %d Number\n",atoi(argv[2]));
      if((fp = fopen(argv[3],"w+")) == NULL){
        printf("Can't create file\n");
      } else {
        srand(time(NULL));
        fprintf(fp,"%d\n",atoi(argv[2]));

        for(i = 0; i < atoi(argv[2]);i++)
          fprintf(fp,"%d\n",1000-rand()%2000);

        rewind(fp);
        fscanf(fp,"%d",&num);
        arr = readalist(fp,num);
        fclose(fp);

     printlist(arr,num);
        begin = clock();
        quicksort(arr,0,num-1);
        end = clock();
     printlist(arr,num);


      }
    } else if(!strcmp(argv[1],"n")) {
      if((fp = fopen(argv[2],"r")) == NULL){
        printf("Can't open file\n");
      } else {
        fscanf(fp,"%d",&num);
        arr = readalist(fp,num);
        fclose(fp);

     printlist(arr,num);
        begin = clock();
        quicksort(arr,0,num-1);
        end = clock();
      printlist(arr,num);
      }
    }
//    TIME(begin,end);
  }
  return 0;
}

void printlist(VARTYPE *arr,int num){
  int i;
  for (i = 0 ; i <num ;i++){
    printf("%d\t",arr[i]);
  }
  printf("\n");
}


VARTYPE * readalist(FILE *s,int num){
  int i;
  VARTYPE *arr;
  arr = (VARTYPE *)malloc(sizeof(VARTYPE)*num);
  for(i = 0; i < num;i++){
    fscanf(s,"%d",&arr[i]);
  }
  return arr;
}



void quicksort(VARTYPE *A,int q,int r){
     if(q > r) return ;
     int left,right,p,
          id = (q+r)/2;
     printf("\n%d",id);
	
  
     p = partion(A,q,r,id);
     quicksort(A,q,p-1);
     quicksort(A,p+1,r);
     
}




int partion(VARTYPE *A,int q,int r,int pivotI){
  int i,sI,pI,pivotV;
  pivotV = A[pI];
  swap(&A[pI],&A[r]);
  sI = q;

  for(i = q; i < r;i++){
    if(A[i]<pivotV){
      swap(&A[i],&A[sI]);
      sI++;
    }
  }
  swap(&A[sI],&A[r]);
  return sI;
}

void swap(VARTYPE *a,VARTYPE *b){
  VARTYPE temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
