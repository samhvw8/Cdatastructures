#include <stdio.h>
#define MAX 100

void replace(char *str,char be,char ap);
void mfflush();


int main() {
  char str[MAX];
  char be,ap;
  printf("\n Input : ");scanf("%[^\n]",str);getchar();
  printf(" character want to replace : ");scanf("%c",&be);getchar();
  printf(" Replace %c with : ",be);scanf("%c",&ap);
  
  replace(str,be,ap);
  printf("\n After replace : ");printf("%s\n",str);
 
  return  0;

}
void replace(char *str,char be,char ap){
   while( *str != '\0'){
    if(*str == be ) *str = ap;
    str++;    
  }
}
