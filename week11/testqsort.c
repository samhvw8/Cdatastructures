#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10


int cmp(const void *a,const void *b){
  int *va = *((int **)(a));
  int *vb = *((int **)(b));
  return *va - *vb;
}


int main(int argc, char *argv[])
{

  int **arr,i;
  int l = 0;
  arr = (int **)malloc(sizeof(int *)*MAX);
  for (i = 0; i < MAX; i++) {
    arr[i] =(int *) malloc(sizeof(int));
    *arr[i] = rand()%100 ;
  }
  printf("\n");
  for (i = 0; i < MAX; i++) {

    printf("%d ",*arr[i]);

  }
  printf("\n");
  qsort(arr,MAX,sizeof(int*),cmp);

  for (i = 0; i < MAX; i++) {

    printf("%d ",*arr[i]);

  }
  printf("\n");



  return 0;
}



