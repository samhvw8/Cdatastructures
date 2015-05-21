#include<stdio.h>

#include "linkstack.h"

int num(char *a){
  int i = 0;
  while(*a != '\0'){
    i++;a++;
  }
  return i;
}

int main(){
  StackType a = NULL;
  int i;


  for (i = 0; i < 10; i++) push(i,&a);
  for (i = 0; i < 10; i++) printf("%d\t",pop(&a));
    printf("\n");

  return 0;
}
