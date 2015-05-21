
#include "Queue.h"


void Qinstall(Queue *queue){
  if(queue == NULL) queue = calloc(1,sizeof(queue));
  if(queue->llist == NULL) queue->llist = calloc(1,sizeof(llist));
  queue->llist->c = NULL;
  queue->llist->l = NULL;
  queue->llist->r = NULL;
  queue->num = 0;
}
int empty(Queue queue){
  return queue->num == 0;
}
void Enqueue(ETYPE el,Queue *queue){
    insertE(queue->llist,el);
    queue->num++;
}
ETYPE Dequeue(Queue *queue){
  if(!empty(*queue)) {
    ETYPE val = queue->llist->r->v;
    delNode(queue->llist,queue->llist->r);
    queue->num--;
    return val;
  }
}

void Qremove(Queue *queue){
  if(queue != NULL) freelist(queue->llist->r);
  free(queue);
}
