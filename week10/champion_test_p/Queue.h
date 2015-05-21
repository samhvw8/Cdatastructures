
/*
  Author : Ginz
  Queue with Double linklist
  Update date : 07/05/2015
  update to more ...

*/



#ifndef _QUEUE_H_GIN_
#define _QUEUE_H_GIN_

#include "dlink.h"
typedef struct queue{
  llist l;
  int num;
} Qdef;

typedef Qdef * Queue;

void Qinstall(Queue *q);
int empty(Qdef queue);
void Enqueue(void *  el,Queue queue);
void *  Dequeue(Queue queue);
void Qremove(Queue *queue);

#endif
