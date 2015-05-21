#include <stdio.h>
#include <stdlib.h>
#include "dlink.h"

#include "Queue.h"

#define LIMITZ 32767

int main(){

  Queue *q = NULL;
  Qinstall(&q);

  printf("\tInput : ");

  while (1) {
    int val ;
    scanf("%d",&val);
    if(val != LIMITZ ) {
      if(q->num < 10)  Enqueue(val,q);
      else{
        printf("\tout: %d |",Dequeue(q));
        Enqueue(val,q);

      }
    } else break;
  }
  printf("\n\t Exit Program !!\n");
  Qremove(&q);


  return 0;
}
