#include <stdio.h>
#include <stdlib.h>
#define MAX 50
typedef int Eltype;
typedef Eltype StackType[MAX];
int top;

void Initialize(StackType stack){
  top = 0;
}
int empty(StackType stack){
  return top == 0;
}
int full(StackType stack){
  return top == MAX;
}
void push(Eltype el,StackType stack){
  if(full(stack)) printf("\t\tStack overflow !! \n");
  else stack[top++] = el;
}
Eltype pop(StackType stack){
  if(!empty(stack))stack[--top];
}
