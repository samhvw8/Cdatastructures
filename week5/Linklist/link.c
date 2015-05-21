#include "link.h"

void insertAtoN(VARTYPE *arr);
void printN();

int main(int argc, char *argv[])
{
  VARTYPE a[] = {5,1,3,2,5,6};
  insertAtoN(a);

  //insertNa(findNode(5),9);
  delNode(findNode(2));
  printN();
  return 0;
}


void printN(){
  node *s = root;
  while (s != NULL) {
    printf("%d ",s->element);
    s = s->next;
  }
  printf("\n");
}


void insertAtoN(VARTYPE *arr){
  int i;
  int num = *arr;arr++;
  for (i = 0; i < num; i++) {
    insertN(*arr);
    arr++;
  }
}

