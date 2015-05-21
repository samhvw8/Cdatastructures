#include <stdio.h>
#include <stdlib.h>

void copy(FILE *p,FILE *p2);

int main(int argc, char *argv[])
{
  FILE *p,*p2;
  if(argc != 3) printf("Wrong command.\nThe command format is sourse-file destination-file\n");
  else{
    if((p = fopen(argv[1],"r")) == NULL ) printf("Can't Read file\n");
    else if((p2 = fopen(argv[2],"w")) == NULL ) printf("Can't create file \n");
    else {
      copy(p,p2);
    }
    fclose(p);
    fclose(p2);
  }
  return 0;
}
void copy(FILE *sp,FILE *dp){
  int c;
  while ((c = fgetc(sp)) != EOF) {
    fprintf(dp,"%c",c);
    putchar(c);
  }
  printf("\n");
}

