#include "Ginz.h"
#define MAX 100

int main(int argc, char *argv[])
{ 
  int i;
  char article[][MAX] = {"the","a","one","some","any"};
  char prepos[][MAX] = {"to","from","over","under","on"};
  char verb[][MAX] = {"drove","jumped","ran","walked","skipped"};
  char noun[][MAX] = {"boy","girl","dog","town","car"};
  srand(time(NULL));
  
  

  for (i = 0; i < 10; i++) {
    indent(2);
    printf("%s %s %s %s %s %s\n",article[rand()%5],noun[rand()%5],verb[rand()%5],prepos[rand()%5],article[rand()%5],noun[rand()%5]);
  }
  
  return 0;
}
