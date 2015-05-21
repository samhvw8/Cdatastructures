/*
  Author : Ginz
  Queue with Double linklist
  Update date : 06/05/2015
  Change Change type to void *

*/



#ifndef _QUEUE_H_GIN_
#define _QUEUE_H_GIN_

#include "dlink.h"
typedef struct queue{
  llist l;
  int num;
} Queue;


void Qinstall(Queue **q);
int empty(Queue queue);
int full(Queue queue);
void Enqueue(void *  el,Queue *queue);
void *  Dequeue(Queue *queue);
void Qremove(Queue **queue);

#endif
