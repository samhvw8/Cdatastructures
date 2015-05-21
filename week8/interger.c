#include <stdio.h>
#include "Queue.h"


int main(){
  Queue q;
  Qinstall(&q);
  int i;
  printf("\tInput : ");
  while(1) {
    int val;
    scanf("%d",&val);
    if(val != -1) Enqueue(val,&q);

  }





}
