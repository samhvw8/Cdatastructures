/*
  Calulate Postfix expressing in C
  Author : SamHV
*/
#include "linkstack.h"
#include "Ginz.h"
#include <string.h>
#include <stdlib.h>





void VSremove(StackType *s);
char *getnum(char **s);
int calculate(StackType *S);
StackType *postfix(char *s);
StackType *Sreverse(StackType *s);
void show(StackType *s);

int main(int argc,char **argv){
  
  StackType *zpostfix = NULL;
  char s[1000];
  
  while (1) {
    switch(getmenu("Import Expression (infix);Show postfix;Calculate",3,1)){
    case 1:
      VSremove(zpostfix);
      printf("\tInput Expression :");
      scanf("%[^\n]",s);mfflush();
      zpostfix = postfix(s);
      // import to stack
      zpostfix = Sreverse(zpostfix);break;
    case 2:
      if(zpostfix == NULL) printf("\t\tImport Expression first !!\n");
      else {
        printf("\tPostfix :"); 
        show(zpostfix);  
      }break;
    case 3: 
      if(zpostfix == NULL) printf("\t\tImport Expression first !!\n");
      else {
        printf("\tresult :");
        printf("%d\n",calculate(zpostfix));
      } break;
    case 0 :  
      printf("\t\tExit Program !!\n");
      VSremove(zpostfix);
      return 0;
    }
  }
}
void VSremove(StackType *s){
  if(s == NULL) return ;
  while (!empty(*s)) {
    free(pop(s));
  }
  free(s);
  s = NULL;
}

char *getnum(char **s){ 
  // get number from string and move the pointer
  int i = 0; // index
  char *result;


  while (**s != ' ' && **s != '(' && **s != ')' && **s != '+' && **s != '-' && **s != '*' && **s != '/' && **s != '!' ) {
    // count number
    (*s)++;
    i++;
  }
  *s = *s-i; /* restore to store loction  */

  result = (char *)malloc(sizeof(char) * (i+1));
  if(result == NULL){
    fprintf(stderr,"\t\t[ERROR] : Can't allocate memory on function char * getnum \n");
    exit(EXIT_FAILURE);
  } else {
    while (**s != ' ' && **s != '(' && **s != ')' && **s != '+' && **s != '-' && **s != '*' && **s != '/' && **s != '!' ) {
      *result = **s;
      (*s)++;
      result++;
    }
    *result = '\0';
    return result-i;
  }
}
int calculate(StackType *S){
  
  StackType *temp;
  temp = (StackType *)malloc(sizeof(StackType));
  Sinstall(temp);
  int value;
  while (!empty(*S)) {
    char *z = pop(S);
    if(*z >= '0' &&  *z<= '9') push(z,temp);
    else {
      if(empty(*temp)) {
        fprintf(stderr,"\t\t[ERROR] - Wrong input expression \n");
        exit(EXIT_FAILURE);
      }
      else{
        if(empty(*temp)) {
          fprintf(stderr,"\t\t[ERROR] - Wrong input expression \n");
          exit(EXIT_FAILURE);
        }
        int a = atoi(pop(temp));
        if(empty(*temp)) {
          fprintf(stderr,"\t\t[ERROR] - Wrong input expression \n");
          exit(EXIT_FAILURE);
        }
        int b = atoi(pop(temp));
        if(*z == '+') {
          char *m_num = (char *)malloc(sizeof(char) * 100);
          sprintf(m_num, "%d", (a+b));
          push(m_num,temp);
        }
        else if(*z == '*') {
          char *m_num = (char *)malloc(sizeof(char) * 100);
          sprintf(m_num, "%d", (a*b));
          push(m_num,temp);
        }
        else if(*z == '/') {
          char *m_num = (char *)malloc(sizeof(char) * 100);
          sprintf(m_num, "%d", (b/a));
          push(m_num,temp);

        }
        else if(*z == '-') {
          char *m_num = (char *)malloc(sizeof(char) * 100);
          sprintf(m_num, "%d", (b-a));
          push(m_num,temp);
        }
      }
    }
  }
  
  value = atoi(pop(temp));
  return value;
}

StackType *postfix(char *s){
 
  StackType *result,*operator;
  
  //
  result = (StackType *)malloc(sizeof(StackType));
  operator = (StackType *)malloc(sizeof(StackType));  
  //
  Sinstall(result);  Sinstall(operator);
  //
 
  while (1) {
    if(*s == '(' || *s == ')' || *s == '[' || *s == '{' || *s == ']' || *s ==  '}'){
      if(*s == '(' || *s == '[' || *s == '{') {
        char *op = (char *)malloc(sizeof(char)*2);
        *op = *s;op++;*op = '\0';op -= 1;
        push(op,operator);
      }
      else {
        char *c = pop(operator);
      
        while (*c != '(' && *c != '[' && *c != '{' ) {
          push(c,result);
          c = pop(operator);
        }
      
      }
      s++;
    } else
      // num
      if(*s >= '0' && *s <= '9'){
        push(getnum(&s),result);
      } else   // operator
        if(*s == '+' || *s == '-' || *s == '*' || *s == '/' ){
          if(empty(*operator)) {
            char *op = (char *)malloc(sizeof(char)*2);
            *op = *s; op++; *op = '\0'; op -= 1;
            push(op,operator);
          } else {
            int o = -1;
            char *c = pop(operator);
              
            if(*c == '+' || *c == '-' || *c == '/' || *c == '*' ){
              if(*s == '+' || *s == '-' ) {// lower or equal
                o = 0;
              } else { //higher or equal
                if(*c == '/' || *c == '*'){
                  o = 0;
                } else if(*c == '+' || *c == '-') {
                  o = 1;
                }
              }
              if(o == 0){
                char *op = (char *)malloc(sizeof(char)*2);
                *op = *s;op++;*op = '\0';op -= 1;
                push(c,result);
                push(op,operator);
              } else {
                char *op = (char *)malloc(sizeof(char)*2);
                *op = *s;op++;*op = '\0';op -= 1;
                push(c,operator);
                push(op,operator);
              }
            }else { 
              char *op = (char *)malloc(sizeof(char)*2);
              *op = *s;op++;*op = '\0';op -= 1;
              push(c,operator);
              push(op,operator);
            }
          }s++;
        } else s++;   
         
    if(*s == '\0') break;
  }
  while (!empty(*operator)) {
    char *c = pop(operator);
    push(c,result);
  }

  Sremove(operator);

  return result;
    
}
StackType *Sreverse(StackType *s){
  StackType *z;
  z = (StackType *)malloc(sizeof(StackType));
  Sinstall(z);
  
  while (!empty(*s)) {
    char *c = pop(s);
    push(c,z);
  }
  
  return z;
}

void show(StackType *s){
  StackType *temp = (StackType *)malloc(sizeof(StackType));
  Sinstall(temp);
  while (!empty(*s)) {
    char *c = pop(s);
    printf("%s ",c);
    push(c,temp);
  }
  printf("\n");
  while (!empty(*temp)) {
    char *c = pop(temp);
    push(c,s);    
  }
}
