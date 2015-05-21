#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int dicOrder(char **a,char **b){
  if(**a == '\0' && **b != '\0') return -1;
  if(**a != '\0' && **b == '\0') return 1;
  if(**a == '\0' && **b == '\0') return 0;
  if(**a < **b) return -1;
  else if(**a > **b) return 1;
  else {
    (*a)++;(*b)++;
    return dicOrder(a,b);
  }
}



int main(){
  char a[] = "linux";
  char b[] = "linuxx";

  int c;
  if((c = strcmp(a,b)) == 0) printf("\n\t %s is same %s\n",a,b);

  else if(c < 0) printf("\n\t %s is before %s\n",a,b);
  else printf("\n\t %s is before %s\n",b,a);
  printf("%d \n",c);
}

