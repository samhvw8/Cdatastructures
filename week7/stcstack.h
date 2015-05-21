#define MAX 50
typedef int Eltype;
typedef struct StackRec{
  Eltype storage[MAX];
  int top;

} StackType;

void Initialize(StackType *stack){
  (*stack).top = 0;
}
int empty(StackType stack){
  return stack.top == 0;
}
int full(StackType stack){
  return stack.top == MAX;
}
void push(Eltype el,StackType *stack){
  if(full(*stack)) printf("\t\tStack overflow !! \n");
  else stack->storage[stack->top++] = el;
}
Eltype pop(StackType *stack){
  if(!empty(*stack))(*stack).storage[--(*stack).top];
}
