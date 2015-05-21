#include  <stdio.h>
#include <stdlib.h>
#include <time.h>


int binSearch(int *L,int Target,int size){
  int Mid,
    Lo = 0,
    Hi = size -1;
  while(Lo <= Hi){
    Mid = (Lo + Hi) /2;
    if(L[Mid] == Target) return Mid;
    else if(Target < L[Mid]) Hi = Mid -1;
    else Lo = Mid +1;
  }
  return -1;
}

int rBinSearch(int *L,int Target,int Lo,int Hi){

  if(Hi == Lo) if(L[Hi] == Target) return Hi; else return -1;
  int Mid = (Lo + Hi) /2;
  if(L[Mid] == Target) return Mid;
  else if(L[Mid] > Target )return rBinSearch(L,Target,Lo,Mid - 1);
  else return rBinSearch(L,Target,Mid + 1,Hi);
}

int main(){
  clock_t  s,e;
  int *A;
  A =(int *)malloc(sizeof(int)*100000001);
  size_t i;
  for (i = 1 ; i <= 100000000;i++) A[i-1] = i;
  int findV = 7;
  s = clock();
  int z = rBinSearch(A,findV,0,100000001);
  e = clock();
  printf("\n \t Loc of %z : %d\nTime %.5lf\n",findV,z,(double)(e-s)/CLOCKS_PER_SEC);
}
