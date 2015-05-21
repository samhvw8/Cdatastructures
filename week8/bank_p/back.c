#include <stdio.h>

#include "Queue.h"

#define Qbank 2


q *qbank;
int timecur;
void createQbank(){
  qbank = (q *)malloc(sizeof(q)*Qbank);
  int i ;
  for ( i = 0 ; i < Qbank ;i++){
    q-> end = {0,0};
  }
}

int timecmp(time a,time b){
  if(a.h > b.h) return 1;
  else if(a.h < b.h) {
    return -1;
  }
  else {
    if(a.m > b.m) return 1;
    else if(a.m < b.m) return -1;
    else return 0;
  }
}

void utime(time *t){
  int p = 0;
  if(t->m > 60) {
    p = (t->m)/60;
    t->m = (t->m) % 60;
  }
  t->h += p;
}

void addtowating(Queue *wait,time t,int num){
  wait a[num];
  int i;
  for(i = 0; i < num ;i++) {
    a[i].come = t;
    a[i].wait = {0,0};
  }
  for (i = 0;i < num ; i++){
    Enqueue(a[i],wait);
  }
}



void process(Queue *done,Queue *wait){
  int i;
  for (i = 0 ; i < Qbank ;i++){
    int c;
    if((c = timecmp(qbank[i].end,wait->l.r->v.come)) == 1) continue;
    else {
      qbank[i].end = Dequeue(wait).come;
      qbank[i].end.m += 15;
      utime(&qbank[i].end);
    }
  }
}



int main(int argc, char *argv[])
{
  Queue *waitL,
    *doneL;
  Qinstall(&waitL);
  Qinstall(&doneL);
  return 0;
}


