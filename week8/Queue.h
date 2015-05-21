typedef int ETYPE;
#include "dlink.h"
typedef stuct {
  llist llist;
  int num;
} Queue;


void Qinstall(Queue *queue);
int empty(Queue queue);
int full(Queue queue);
void Enqueue(ETYPE el,Queue *queue);
ETYPE Dequeue(Queue *queue);
void Qremove(Queue *queue)
