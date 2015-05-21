typedef  void * ETYPE;


#include "Ginz.h"
#include "linkstack.h"
void SremoveV(StackType *stack){ // for void
  if(stack != NULL) freelist(stack);
}
// free list for void
void freelistV(node **r){
  if (r == NULL) return;
  if (*r == NULL) return;
  node *to_free = *r;
  while(to_free != NULL){
    *r = (*r)->next;
    free(to_free->v);
    free(to_free);
    to_free = *r;
  }
}



void numPush(StackType *num,StackType *buff);
int numPop(StackType *num,StackType *buff);
void fundo(StackType *num,StackType *buff);
void fshow(StackType *num);





int main(int argc, char *argv[]){
  StackType num,buff;
  Sinstall(&num);
  Sinstall(&buff);


  for (;;) {
    switch(getmenu("Input;Pop;Undo;Show",4,1)){
    case 1:numPush(&num,&buff);break;
    case 2:numPop(&num,&buff);break;
    case 4:fshow(&num);break;
    case 3:fundo(&num,&buff);break;
    case 0:
      SremoveV(&num);
      SremoveV(&buff);
      printf("\n\t\t\tExit Program !!\n\n");
      return 0;
    }
  }
}

void numPush(StackType *num,StackType *buff){
  int * val = calloc(1,sizeof(int));
  char *m_num,*buf;
  printf("\tWhat Num you want to input : " );scanf("%d",val);mfflush();

  push(val,num); // input number

  m_num = malloc(sizeof(char) * 100);
  sprintf(m_num, "%d", *val);

  buf = malloc(sizeof(char) * 100);
  strcpy(buf,"PUSH ");

  strcat(buf,m_num);

  push(buf,buff); //input buff
  free(m_num);
}



int numPop(StackType *num,StackType *buff){
  if(!empty(*num)) {
    int *v = (int *)pop(num); // pop
    int val = *v;
    free(v);
    char *m_num,*buf;

    m_num = malloc(sizeof(char) * 100);
    buf = malloc(sizeof(char) * 100);
    strcpy(buf,"POP ");
    sprintf(m_num, "%d", val);

    strcat(buf,m_num);
    push(buf,buff); //input buff
    free(m_num);
    return val;
  } else {
    printf("\tHaven't number in stack !!\n"
           "\tPush to stack first !!\n ");
    return 0;
  }
}

void fundo(StackType *num,StackType *buff){
  if(!empty(*buff)) {
    char *s =(char *)pop(buff);
    //    printf("%s\n",s);
    if(!strncmp(s,"PUSH",4)){
      int v = *(int *)pop(num);
      printf("\tUndo Push %d ==> Pop %d\n",v,v);
    }
    else{
      s = s+4;
      int *val = calloc(1,sizeof(int)) ; *val = atoi(s);
      push(val,num);
      printf("\tUndo Pop %d ==> Push %d\n",*val,*val);
      s = s-4;
    }
    free(s);
  } else printf("\tNothing to undo !!\n");
}
void fshow(StackType *num){
  if(!empty(*num)){
    StackType *temp;
    temp = (StackType *)malloc(sizeof(StackType));
    Sinstall(temp);
    /* printf("%d\n",!empty(*num)); */

    printf("\t");
    while(!empty(*num)){
      int *c =(int *)malloc(sizeof(int));
      c = (int *)pop(num);
      printf("%d ",*c);
      push(c,temp);
    }
    printf("\n");

    while(!empty(*temp)){
      int *c = calloc(1,sizeof(int));
      c = (int *)pop(temp);
      push(c,num);
    }
    Sremove(temp);
  } else printf("\tHasn't number in stack !!\n"
                "\tPush first !!\n");
}
