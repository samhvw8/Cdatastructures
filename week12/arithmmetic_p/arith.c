#include "linkstack.h"
#include "Btree.h"
#include "Ginz.h"

void printpretty(tree r,tree T,int m){
  char space[] = "    ";
  if(T == NULL) return ;
  printpretty(r,T->left,m);
  int i,h = m - depth(r,T,0);
  for (i = 0; i < 3*h; i++) {
    printf("%s",space);
  }
  printf("%-s\n",(char *)T->element);
  printpretty(r,T->right,m);
}


/*
void prettyprint(tree t,char *prefix){
  char *prefixend = prefix + strlen(prefix);
  if(t!=NULL){
    printf("%04s",(char *)t->element);
    if(t->left != NULL) if(t->right  == NULL){
        printf("\304");
        strcat(prefix,"    ");
      } else {
        printf("\302");
        strcat(prefix,"\263    ");
      }
    prettyprint(t->left,prefix);
    *prefixend = '\0';
    if(t->right != NULL) if(t->left != NULL) {
        printf("\n%s",prefix);
        printf("\300");
      } else printf("\304");
    strcat(prefix,"    ");
    prettyprint(t->right,prefix);
  }
}
*/
void postfixfromtree(tree t,StackType **Post,void (*order)(tree,StackType **)){
  if(t == NULL) return;
  postfixfromtree(t->left,Post,order);
  postfixfromtree(t->right,Post,order);
  order(t,Post);
}

void addtoStack(tree n,StackType **Post);

long factorial(int n);

char *getnum(char **s);

StackType *Sreverse(StackType *s);

StackType *postfix(char *s);

int calculate(StackType *S);

tree impTree(StackType *S);

void show(StackType *s);

void funtravel(tree a);

void travelfree(tree a);

int main(void){

  StackType *zpostfix = NULL;

  tree aritree = NULL;

  MakeNullTree(&aritree);

  char s[1000];
  // char strprefix[] = "";
  while (1) {
    switch(getmenu("Import Expression (infix);Show Traveral/Tree;Reverse tree;Calculate",4,1)){
    case 1:
      // clear
      Sremove(zpostfix);
      if(aritree != NULL){
        freetree(&aritree);
        MakeNullTree(&aritree);
      }
      //


      printf("\tInput Expression :");
      scanf("%[^\n]",s);mfflush();
      zpostfix = postfix(s);
      // import to stack
      zpostfix = Sreverse(zpostfix);

      //show(zpostfix);
      // import to tree
      aritree = impTree(zpostfix);
      break;
    case 2:
      if(aritree == NULL) printf("\t\tImport Expression first !!\n");
      else {

        printf("\tIn order travel  :");
        in_order(aritree,funtravel);
        printf("\n");

        printf("\tPost order travel  :");
        post_order(aritree,funtravel);
        printf("\n");

        printf("\tPre order travel  :");
        pre_order(aritree,funtravel);
        printf("\n");
        printpretty(aritree,aritree,height(aritree));
        printf("\n");
      }break;
    case 3:
      if(aritree == NULL) printf("\t\tImport Expression first !!\n");
      else {
        reversetree(&aritree);
        printf("\t\tReverse tree complete !!\n");
      }break;
    case 4:
      if(aritree == NULL) printf("\t\tImport Expression first or can't Generate postfix !!\n");
      else {
        //show(zpostfix);
        zpostfix = (StackType *)malloc(sizeof(StackType));
        Sinstall(zpostfix);

        postfixfromtree(aritree,&zpostfix,addtoStack);

        zpostfix = Sreverse(zpostfix);

        printf("\n\t\t Calculate : %d \n",calculate(zpostfix));
      } break;
    case 0 :
      printf("\t\tExit Program !!\n");
      Sremove(zpostfix);
      freetree(&aritree);
      MakeNullTree(&aritree);
      return 0;
    }
  }
}

void funtravel(tree a){
  if(a != NULL) printf("%s ",(char *)a->element);
}


char *getnum(char **s){
  // get number from string and move the pointer
  int i = 0; // index
  char *result;
  
  while (**s >= '0' && **s <= '9' ) {
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
    while (**s >= '0' && **s <= '9') {
      *result = **s;
      (*s)++;
      result++;
    }
    *result = '\0';
    return result-i;
  }
}

tree impTree(StackType *S){

  StackType *temp;
  temp = (StackType *)malloc(sizeof(StackType));
  Sinstall(temp);

  while (!empty(*S)) {
    char *z = pop(S);
    if(*z >= '0' &&  *z<= '9') {
      tree a = CreateNode(z);
      push(a,temp);
    }
    else { // *z not string of number
      if(empty(*temp)) {
        fprintf(stderr,"\t\t[ERROR] - 1  Wrong input expression \n");
        exit(EXIT_FAILURE);
      }
      else{
        tree a = (tree)pop(temp);
        if(*z == '!' ) {
          tree c = createfrom2(z,a,(void *)NULL);
          push(c,temp);
        } else {
          if(empty(*temp)) {
            fprintf(stderr,"\t\t[ERROR] - 2  Wrong input expression \n");
            exit(EXIT_FAILURE);
          }
          tree b = (tree)pop(temp);
          if(*z == '+' || *z == '-' || *z == '*' || *z == '/') {
            tree c = createfrom2(z,b,a);
            push(c,temp);
          }
        }
      }
    }
  }
  tree z = (tree)pop(temp);
  if(!empty(*temp)) {
    fprintf(stderr,"ERROR 3 Input expression !!\n");
    exit(EXIT_FAILURE);
  }
  Sremove(temp);
  return z;
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
        if(*s == '+' || *s == '-' || *s == '*' || *s == '/' || *s == '!'){
          if(*s == '!') {
            char *op = (char *)malloc(sizeof(char)*2);
            *op = *s; op++; *op = '\0'; op -= 1;
            push(op,result);
            s++;
          } else {
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
          }
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
        fprintf(stderr,"\t\t[ERROR] -1z Wrong input expression \n");
        exit(EXIT_FAILURE);
      }
      else{
        int a = atoi(pop(temp));
        if(*z == '!'){
          char *m_num = (char *)malloc(sizeof(char) * 100);
          long zz = factorial(a);
          if(zz == 0)  {
            fprintf(stderr,"\t\t[ERROR] -2z Wrong input expression \n");
            exit(EXIT_FAILURE);
          }
          sprintf(m_num, "%ld", zz);
          push(m_num,temp);
        }
        else {
          if(empty(*temp)) {
            fprintf(stderr,"\t\t[ERROR] -3z Wrong input expression \n");
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
  }
  char *s = pop(temp);
  value = atoi(s);
  free(s);
  return value;
}

long factorial(int n){
  if(n == 0) return 1;
  else return n*factorial(n-1);

}


void addtoStack(tree n,StackType **Post){
  if(n == NULL || Post == NULL) return ;
  push(n->element,*Post);
}
