#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VARTYPE int
#define LIMIT 100000000
#define TIME(BEGIN,END) printf("Time sorting is %.6lf s\n",(double)(END - BEGIN)/CLOCKS_PER_SEC);



void printlist(VARTYPE *arr,int num);
VARTYPE * readalist(FILE *s,int num);
VARTYPE *merge(VARTYPE *a,VARTYPE *b,int num);
VARTYPE *mergesort(VARTYPE *arr,int num);


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
        
       // printlist(arr,num);	
        begin = clock();
        arr = mergesort(arr,num);
        end = clock();
       // printlist(arr,num);
        
        
      }
    } else if(!strcmp(argv[1],"n")) {
      if((fp = fopen(argv[2],"r")) == NULL){
        printf("Can't open file\n");
      } else {
        fscanf(fp,"%d",&num);
        arr = readalist(fp,num);
        fclose(fp);
	
      //  printlist(arr,num);	
        begin = clock();
        arr = mergesort(arr,num);
        end = clock();
      //  printlist(arr,num);
      }
    }
    TIME(begin,end);
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

VARTYPE *merge(VARTYPE *a,VARTYPE *b,int num){
  VARTYPE *c;
  int i,j,z,num2;
  c = (VARTYPE *)malloc(sizeof(VARTYPE)*num);
  i = j = z = 0;
  if(num%2==0){num = num/2;num2=num;}
  else {num = num/2;num2=num+1;}
  
  while(i<num && z<num2){
    if(a[z]>b[i]) {
      c[j] = b[i];
      b[i] = LIMIT;
      j++;
      i++;
    } else {
      c[j] = a[z];
      a[z] = LIMIT;
      j++;
      z++;
    }
  }
   
  
  for(i = 0; i < num2 ; ++i){
    if(a[i] != LIMIT) {c[j] = a[i];j++;}
  }
  for(i = 0; i < num ; ++i){
    if(b[i] != LIMIT) {c[j] = b[i];j++;}
  }
   
  free(a);
  free(b);
  return c;
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



VARTYPE *mergesort(VARTYPE *arr,int num){
  if(num <= 1) return arr;
  VARTYPE *l1,*l2;
  l1 = (VARTYPE *)malloc(sizeof(VARTYPE)*(num/2));
  l2 = (VARTYPE *)malloc(sizeof(VARTYPE)*(num - num/2));
  int i,j;
  i = 0;
  j = 0;
  while (i < num/2) {
       l1[j] = *arr;
       arr++; 
       i++;
  }
  j = 0;
  while (i < num) {
       l2[j] = *arr;
       arr++; 
       i++;
  }

 if(num%2 == 0) l1 = mergesort(l1,num/2);
 else  l1 = mergesort(l1,num/2+1);
  
  l2 = mergesort(l2,num/2);
  return merge(l1,l2,num);
}

