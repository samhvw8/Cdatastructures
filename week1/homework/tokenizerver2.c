#include "Ginz.h"
#define MAXLINE  100
#define MAX 50



char **token(char *s);

int main() {
  char str[MAXLINE],**strtokz;
  while (1) {
    switch(getmenu("Input string;Token",2,1)){
    case 1:printf(" input :");scanf("%[^\n]",str);mfflush();break;  
    case 2:strtokz = token(str);
      indent(2);printf(" After tokenize : \n");printf("%s\n",strtokz[0]);break;
    case 0:indent(2);
      printf("Exit Program !!\n");      return 0;
    }
  }  
}
char **token(char *s){
  char **strtokz;
  int i,j;
  strtokz = (char **)malloc(MAX*MAXLINE*sizeof(char));
  i = j =0;
   while(*s != '\0'){
     if(*s != '\t' && *s != ' ') {
       strtokz[i][j] = *s ;
       s++;j++;
     }
     else {
      
       j = 0; i++;
     }
  }
   return strtokz;
}
