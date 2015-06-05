
/*
  Author : Ginz
  Queue with Double linklist
  Update date : 06/05/2015
  Change Change type to void * , update Function Qremove

*/

#include "Queue.h"


void Qinstall(Queue **q){
  *q = (Queue *)malloc(sizeof(Queue));
  linit(&((*q)->l));
  (*q)->num = 0;
}
int empty(Queue queue){
  return queue.num == 0;
}
void Enqueue(void * el,Queue *queue){
  insertE(&(queue->l),el);
  queue->num++;
}
void * Dequeue(Queue *queue){
     if(!empty(*queue)) {

          void * val = queue->l.r->v;

          delNodeR(&(queue->l));

          queue->num--;

          return val;
     } else {
          printf("\t\tQueue has no value !!\n");
          return NULL;
     }
}

void Qremove(Queue **queue){
  if(queue == NULL) return;
  if(*queue == NULL) return;
  while (!empty(**queue)) {
    free(Dequeue(*queue));
  }
  free(*queue);
  *queue = NULL;
}
