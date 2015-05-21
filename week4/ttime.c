#include <Ginz.h>

int main(int argc, char *argv[])
{
  int i;
  clock_t t1,t2;
  t1 = clock();
  for(i = 0;i<10000;i++)printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
  t2 = clock();
  printf("time :%.5lf sec\n",(double)(t2 -t1)/CLOCKS_PER_SEC);
  return 0;
}
