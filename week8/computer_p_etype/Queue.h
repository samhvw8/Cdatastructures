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
void Enqueue(ETYPE el,Queue *queue);
ETYPE Dequeue(Queue *queue);
void Qremove(Queue **queue);

#endif
