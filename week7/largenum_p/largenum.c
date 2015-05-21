/*
  Calulate Large number in C
  Author : SamHV
 */

#include "linkstack.h"
#include <stdlib.h>
int num(char *a){
  int i = 0;
  while(*a != '\0'){
    i++;a++;
  }
  return i;
}

void sumln(StackType *num1,StackType *num2,StackType *sum){
  int flag = 0;
  int n1,n2,s;
  n1 = n2 = 0;
  while (!(empty(*num1) && empty(*num2))) {
    if(!empty(*num1)) n1 = pop(num1); else n1 = 0;
    if(!empty(*num2)) n2 = pop(num2); else n2 = 0;
    s = n1 + n2;

    if(flag){ s = s+1;flag = 0;}
    if(s > 9) {
      flag = 1;
      s = s-10;
    }
    push(s,sum);
  }
  if(flag)push(1,sum);
}

int compare(StackType *num1,StackType *num2){
  int c = 0; // 0 is num1 = num2 ; 1 is num2 < num1 ; 2 is num2 > num1;
  StackType numz1,numz2;
  numz1 = NULL;
  numz2 = NULL;

  while (1) {
    if(empty(*num1) && !empty(*num2)) {c = 2;break;}
    if(!empty(*num1) && empty(*num2)) {c = 1;break;}
    if(empty(*num1) && empty(*num2)) break;
    
    int n = pop(num1);
    int n2 = pop(num2);
    
    if(n > n2) c = 1; else if(n < n2) c = 2;
    
    push(n,&numz1);
    push(n2,&numz2);
  }
  
  while (!empty(numz1)) {
    int n = pop(&numz1);
    push(n,num1);
  }
  
  while (!empty(numz2)) {
    int n = pop(&numz2);
    push(n,num2);
  }
  
  return c;
}


int minusln(StackType *num1,StackType *num2,StackType *minus){
  int flag = 0;
  int n1,n2,s; // n1 for larger number 
  n1 = n2 = 0;

  int c = compare(num1,num2);
  
  while (!(empty(*num1) && empty(*num2))) {
    if(c == 0) {
      push(0,minus);
      return 0;
    }
    if(c == 1) {
      if(!empty(*num1)) n1 = pop(num1); else n1 = 0;
      if(!empty(*num2)) n2 = pop(num2); else n2 = 0;
    }
    if(c == 2){
      if(!empty(*num2)) n1 = pop(num2); else n1 = 0;
      if(!empty(*num1)) n2 = pop(num1); else n2 = 0;
    }
    int z = 1;
    
    s = n1 - n2;
    if(s < 0 ){
      s = s + 10;
      if(flag) s = s -1;
      flag = 1; 
      z = 0;
    }
    
    if(flag && z){
      if(s == 0) s = 9;
      else if(s > 0){
        s = s -1;
        flag = 0;
      }
    }
    push(s,minus);
  }
  if(c == 2) return 1;
  return 0;  
}
 


int main(int argc,char **argv){

  if(argc != 4 )printf("\t\t Wrong format !\n"
                       "[USAGE:] num - num\n"
			"[USAGE:] num + num\n");

  else {
    StackType num1,num2,ans;
    int i;
    // install
    num1 = NULL;
    num2 = NULL;
    ans = NULL;
    // import to stack

    int m,m1;
    m = m1 = 0;
    char *sn1 = argv[1];
    char *sn2 = argv[3];
    if(argv[1][0]=='-'){ m = 1;sn1++;}
    if(argv[3][0]=='-'){ m1 = 1;sn2++;}
    int size = num(sn1);
    int size2 = num(sn2);
    // num1
    if(m == 1) 
      for(i = 0; i < size;i++){
        push((int)(*sn1-'0'),&num1);
 
        sn1++;
      } 
    else  
      for(i = 0; i < size;i++){
        push((int)(*sn1-'0'),&num1);
  
        sn1++;
      }
    // num2
    if(m1 == 1)
      for(i = 0; i < size2;i++){
        push((int)(*sn2-'0'),&num2);
        sn2++;
      }
    else 
      for(i = 0; i < size2;i++){
        push((int)(*sn2-'0'),&num2);
        sn2++;
      }

   

   
    // minus
    if(argv[2][0] == '-') {
      // 2 number postive
      if(m == 0 && m1 == 0)  if(minusln(&num1,&num2,&ans)) printf("-");
      // first number is negative and second positive
      if(m == 1 && m1 == 0)  {
        sumln(&num1,&num2,&ans);
          printf("-");
      }
      if(m == 1 && m1 == 1){
        if(minusln(&num2,&num1,&ans)) printf("-");
      }
      if(m == 0 && m1 == 1)  {
        sumln(&num1,&num2,&ans);
      }
    }


    // plus
    if(argv[2][0] == '+') {
      if(m == 0 && m1 == 0) {sumln(&num1,&num2,&ans);}
      if(m == 1 && m1 == 0) if(minusln(&num2,&num1,&ans)) printf("-");
      if(m == 1 && m1 == 1)  {
        sumln(&num1,&num2,&ans);
        printf("-");
      }
      if(m == 0 && m1 == 1)  {
        if(minusln(&num2,&num1,&ans)) printf("-");
      }
    }
    


    while(!empty(ans)){
      printf("%d",pop(&ans));
    }
    printf("\n");


    Sremove(&ans);
    Sremove(&num1);
    Sremove(&num2);

  }


  return 0;
}
