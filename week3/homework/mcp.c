#include <Ginz.h>


void cmp(FILE *f,FILE *f1,char *fn,char *fn1);
int main(int argc, char *argv[])
{
  FILE *fi1,*fi2;
  if(argc != 3) printf("Wrong Command format !!\n");
  else {
    if((fi1 = fopen(argv[1],"r"))== NULL ) printf("Can't read file %s!!\n",argv[1]);
    else if((fi2 = fopen(argv[2],"r"))== NULL)  printf("Can't read file %s!!\n",argv[2]);
    else {
        cmp(fi1,fi2,argv[1],argv[2]);
    }
    fclose(fi1);
    fclose(fi2);
  }
  return 0;
}
void cmp(FILE *f,FILE *f1,char *fn,char *fn1){
  char s1[1000],s[1000];
  int l,fg,fg1,count,c2;
  fg = fg1 = count = c2 = 0;
  l  = 0;
  while (1) {
    l++;
    if(fgets(s,1000,f) != NULL)  fg = 1;  else fg = 0;
    if(fgets(s1,1000,f1) != NULL)  fg1 = 1; else fg1 = 0;
    if(fg == 1 && fg1 == 1) {
      if(strcmp(s,s1)!=0) {
        count++;
        if (count == 1 ) printf("The first line different is %d \n",l);
        printf("line %d \n file %s : %s file %s : %s",l,fn,s,fn1,s1);
      }
    }
    else if(fg == 1 && fg1 == 0) {
      c2 += 1;
      if(c2 == 1) printf("\nFile %s is End of file \n",fn1);
    }
    else if(fg1 == 1 && fg == 0)  {
      c2 +=2;
      if(c2 == 2) printf("\nFile %s is End of file \n",fn);
    }
    else if(fg1 == 0 && fg == 0) break;
  }
}
