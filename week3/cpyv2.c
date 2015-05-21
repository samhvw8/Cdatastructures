#include <stdio.h>
#define MAX 1000



void copy(FILE * fin,FILE *fout);
int main(int argc,char **argv){
  FILE *fin,*fout;
  
  if(argc != 3) printf("Wrong command format !!\nFormat is :\"./cpyv2 input-file output-file\"");
  if((fin = fopen(argv[1],"r")) == NULL) {
    printf("Can't Read input file \n");
  }   else {
    if((fout = fopen(argv[2],"w")) == NULL)
      printf("Can't write output file \n");
   else {
    copy(fin,fout);

  }
  fclose(fin);
  fclose(fout);
  }
  return 0;
}

void copy(FILE *fin,FILE *fout){
  char s[MAX];
  
  while((fgets(s,MAX,fin)) != NULL) {
    fputs(s,fout);
   }
}
