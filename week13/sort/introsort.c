#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>



#define VARTYPE int
#define TIME(BEGIN,END) printf("Time sorting is %.6lf s \n",(double)(END - BEGIN)/CLOCKS_PER_SEC);




void iSortS(VARTYPE *A,int num);
void introsort(VARTYPE *A,int maxdepth,int num);
int partion(VARTYPE *A,int q,int r);
void Heapsort(VARTYPE *arr,int num);
void BuildHeap(VARTYPE *arr,int num);
void Heapify(VARTYPE *arr,int loc,int num);
void swap(VARTYPE *a,VARTYPE *b);
void printlist(VARTYPE *arr,int num);
VARTYPE * readalist(FILE *s,int num);
int main(int argc, char const *argv[])
{
  clock_t begin,end;
  FILE *fp;
  VARTYPE *arr;
  int i,num;
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


        //printlist(arr,num);	
        begin = clock();
        iSortS(arr,num);
        end = clock();  
        //printlist(arr,num);
      

      }
    } else if(!strcmp(argv[1],"n")) {
      if((fp = fopen(argv[2],"r")) == NULL){
        printf("Can't open file\n");
      } else {
        fscanf(fp,"%d",&num);
        arr = readalist(fp,num);
        fclose(fp);

        //printlist(arr,num);	
        begin = clock();
        iSortS(arr,num);
        end = clock();  
        //printlist(arr,num);
        

      }
    }
    
    TIME(begin,end);
  }
  return 0;
}
void iSortS(VARTYPE *A,int num){
  introsort(A,floor(log(num))*2,num);
}

void introsort(VARTYPE *A,int maxdepth,int num){
  int p;
  VARTYPE *Az;
  if(num<= 1) return;
  else if (maxdepth == 0) Heapsort(A,num);
  else{
    Az = A;
    p = partion(A,0,num-1);
    Az = Az + p + 1;
    introsort(A,maxdepth-1,p+1);
    introsort(Az,maxdepth-1,num-p-1);
  }
}


int partion(VARTYPE *A,int q,int r){
  int i,sI,pivotI,pivotV;
  pivotI = q;
  pivotV = A[pivotI];
  swap(&A[pivotI],&A[r]);
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





void Heapsort(VARTYPE *arr,int num){
  int i;
  BuildHeap(arr,num);
  
  for(i = num-1 ; i>=1 ; i--){
    swap(&arr[0],&arr[i]);
    Heapify(arr,0,i);
  }
}
void BuildHeap(VARTYPE *arr,int num){
  int i;
  for(i = num/2;i>=0;i--) Heapify(arr,i,num);
}

void Heapify(VARTYPE *arr,int loc,int num){
  int left,right,locmax;
  loc = loc +1;
  left = 2*loc;
  right = left+1;
  
  if(left <= num && arr[left-1] > arr[loc-1]) locmax = left; else locmax = loc;
  if(right <= num && arr[right-1] > arr[locmax-1]) locmax = right;
  
  if(locmax != loc) {
    swap(&arr[loc-1],&arr[locmax-1]);
    Heapify(arr,locmax-1,num);
  }
}

void swap(VARTYPE *a,VARTYPE *b){
  VARTYPE temp;
  temp  = *a;
  *a  = *b;
  *b = temp;
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
