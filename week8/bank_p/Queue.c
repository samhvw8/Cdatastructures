
#include "Queue.h"

void Qinstall(Queue **q){
  *q = (Queue *)malloc(sizeof(Queue));

  linit(&((*q)->l));
  (*q)->num = 0;
}
int empty(Queue queue){
  return queue.num == 0;
}
void Enqueue(ETYPE el,Queue *queue){
  insertE(&(queue->l),el);
  queue->num++;
}
ETYPE Dequeue(Queue *queue){
  if(!empty(*queue)) {
    ETYPE val = queue->l.r->v;
    delNodeR(&(queue->l));
    queue->num--;
    return val;
  } else {
    printf("\t\tQueue has no value !!\n");
    return ;
  }
}

void Qremove(Queue **queue){
  if(queue == NULL) return;
  if(*queue == NULL) return;
  freelist((*queue)->l.r);
  free(*queue);
  *queue = NULL;
}
