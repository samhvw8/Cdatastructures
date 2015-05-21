
#include<Ginz.h>

char *subStr(char *s1,int offset,int number);
int main(){
  char s[] = "Test 1 2 3 4 5 !!!";
  int os,num;
  char *ss;
  printf("String test : %s\n",s);
  printf("Input offset value : ");scanf("%d",&os);
  printf("Input number value : ");scanf("%d",&num);
  if((ss = subStr(s,os,num)) == NULL) {
    printf("Error or NULL value return !!\n");
  } else printf("output: \"%s\"\n",ss);
  return 0;
}


char *subStr(char *s1,int offset,int number){
  char *p;

  if(offset > strlen(s1)+1 || offset < 0){
    printf("wrong input offset !!\n");
    if(number < 0) {
      printf("wrong input number !!\n");
    }
    return NULL;
  } else {
    if(number < 0) {
      printf("wrong input number !!\n");
      return NULL;
    } else {
      p = (char *)malloc(sizeof(int)*number);


      if(offset + number >= strlen(s1)){
        s1 += offset;
        strcpy(p,s1);
      } else {
        s1 += offset;
        strncpy(p,s1,number);
      }
    }
  }
}
