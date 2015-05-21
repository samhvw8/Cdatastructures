/*
  Simulate Process on OS
  Author : Ginz
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "Ginz.h"




unsigned long max_mem_c = 0; // max memory computer
unsigned int max_pro_c = 0;// max process computer

unsigned long free_mem_c = 0; // max memory computer
unsigned int free_pro_c = 0;// max process computer


program *Createp();
void addProgram(Queue *wait);
void killProgram(Queue *run);
void showListprocess(Queue *run,Queue *wait);
void refresh(Queue *run,Queue *wait);
void update(Queue *run);


int main(int argc, char *argv[]){
  Queue *wait = NULL;
  Queue *run = NULL;
  Qinstall(&wait);  Qinstall(&run);
  int firstrun = 0 ;
  while (1) {
    switch(getmenu("Set Computer Detail (Procress/Memory);Add program;Kill program running;Show list process",4,1)){
    case 1:
      printf("\tSet Max process computer : ");scanf("%u",&max_pro_c);mfflush();
      printf("\tSet Max memory computer : ");scanf("%lu",&max_mem_c);mfflush();
      if(firstrun == 0) {
        free_mem_c = max_mem_c;
        free_pro_c = max_pro_c;
        firstrun =1;
      } break;

    case 2:if(!firstrun) printf("\t\t Need Set Computer Detail first !! \n");
      else {
        addProgram(wait);
        refresh(run,wait);
      }
      break;
    case 3:
      if(!firstrun) printf("\t\t Need Set Computer Detail first !! \n");
      else {
        killProgram(run);
        refresh(run,wait);
      }break;
    case 4:
      if(!firstrun) printf("\t\t Need Set Computer Detail first !! \n");else showListprocess(run,wait);break;
    case 0:
      printf("\t\tExit Program !!\n\n");
      Qremove(&wait);
      Qremove(&run);
      return 0;
    }
  }



  return 0;
}


void addProgram(Queue *wait){
  program add;

  printf("\tProgram's name : ");scanf("%[^\n]",add.name);mfflush();
  printf("\tProgram %s's ID :",add.name);scanf("%u",&add.ID);mfflush();
  printf("\tMemory program %s need :",add.name);scanf("%lu",&add.memory);mfflush();



  if(add.memory > max_mem_c ) {

    printf("\t\tProgram you want to add has bigger memory than computer memory !!\n"
           "\t==> Program can not add to waiting procress !!\n"
           "\t\tAdd new Program or correct your program's detail !!\n");
    return;
  }
   Enqueue(add,wait);
}
void killProgram(Queue *run){
  int found = 0;
  node *p = NULL ;
  if(getmenu("Kill by Name;KILL by ID",2,0)){
    char name[30];
    printf("\t\tWhat is program name you want to kill : >");scanf("%[^\n]",name);mfflush();

   p = run->l.r;

    while (p != NULL) {
      if(strcmp(name,p->v.name) == 0){
        found = 1 ;
        break;
      }
      p = p->next;
    }
  } else {
    unsigned int id;
    printf("\t\tWhat is program id you want to kill : >");scanf("%u",&id);mfflush();

    p = run->l.r;

    while (p != NULL) {
      if(id == p->v.ID){
        found = 1 ;
        break;
      }
      p = p->next;
    }
  }
  if(!found) printf("\t\tProgram isn't on running list !!");
  else {
    delNode(&(run->l),p);
    free_pro_c++;
    free_mem_c += p->v.memory;
    printf("\t\tKill program Success !!");
  }
}

void update(Queue *run){
  node *p = run->l.r;
  free_mem_c = max_mem_c;
  while (p!=NULL) {
    free_mem_c -= p->v.memory;
    p = p ->next;
  }
  free_pro_c = max_pro_c - run->num;
}

void refresh(Queue *run,Queue *wait){
  if(!empty(*run)) update(run);

  if(free_pro_c > 0){
    if(free_mem_c >= wait->l.r->v.memory) {
      Enqueue(Dequeue(wait),run);
      if(!empty(*wait)) refresh(run,wait);
    }
  }
}


void showListprocess(Queue *run,Queue *wait){
  printf("\t\t\t System :\n");
  printf("\t\tFree memory : %lu",free_mem_c);
  printf("\t\tFree Process : %u\n",free_pro_c);;


  if(!empty(*run)){
    printf("\t\t Runining Process : \n");
    node *p = run->l.r;
    int i = 0;
    printf("\t\t%-3s %-30s %-15s %s\n","No","Name","ID","Memory");
    while (p != NULL) {
      printf("\t\t%-3d %-30s %-15u %lu\n",i + 1,p->v.name,p->v.ID,p->v.memory);
      p = p ->next;
      i++;
    }
  }
  if(!empty(*wait)){
    printf("\t\t Waiting Process : \n");
    node *p = wait->l.r;
    int i = 0;
    printf("\t\t%-3s %-30s %-15s %s\n","No","Name","ID","Memory");
    while (p != NULL) {
      printf("\t\t%-3d %-30s %-15u %lu\n",i + 1,p->v.name,p->v.ID,p->v.memory);
      p = p ->next;
      i++;
    }
  }
}

