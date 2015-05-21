#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
  FILE *f;
  char c[] = "test !!!!";
  char buff[20];

  f = fopen("test","w+");

  fwrite(c,strlen(c) +1,1,f);
  rewind(f);
  fread(buff,strlen(c)+1,1,f);
  fclose(f);
  printf("!!%s!!\n",buff);
}
