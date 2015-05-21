#include "Ginz.h"
#define MAXLINE  100



void token(char *s);

int main() {
  char str[MAXLINE];
 
  while (1) {
    switch(getmenu("Input string;Token",2,1)){
    case 1:printf(" input :");scanf("%[^\n]",str);mfflush();break;  
    case 2:token(str);
      indent(2);printf(" After tokenize : \n");printf("%s\n",str);break;
    case 0:indent(2);
      printf("Exit Program !!\n");      return 0;
    }
  }  
}
void token(char *s){
  while(*s != '\0'){
    if(*s != '\t' && *s != ' ') s++;
    else *s = '\n';
  }
}
