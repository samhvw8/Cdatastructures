//typedef int VARTYPE;
typedef struct node node;
struct node {
  VARTYPE element;
  node *next;
  node *pev;
};

node *root = NULL;
node *last = NULL;
node *cur = NULL;


// make node
node *makeNode(VARTYPE val){
  node *new = (node *)malloc(sizeof(node));
  new->element = val;
  new->next = NULL;
  new->pev =NULL;
  return new;
}

// insert end of list
void insertE(VARTYPE val){
  node *p = makeNode(val);

  if(root == NULL){
    root = p;
    last = p;
    cur  =p;
  } else {
    last->next = p;
    p->pev = last;
    last = p;
    cur =p;
  }
}
// insert node before
void insertNb(node *p,VARTYPE val){
  node *q = makeNode(val);

  if(root == NULL) {
    insertE(val);
    cur =q;
    free(q);
  } else if(p == root){
    root = q;
    p->pev = q;
    q->next = p;
    cur = q;
  }else {
    p->pev->next = q;
    q->pev = p->pev;
    cur = q;
    p->pev = q;
    q->next = p;
  }
}
//insert node after
void insertNa(node *p,VARTYPE val){
  node *q = makeNode(val);
  if(root ==NULL){
    insertE(val);
    free(q);
  } else if(p == last){
    last =q;
    p->next = q;
    q->pev = p;
    cur = q;
  } else {
    p->next->pev = q;
    q->next = p->next;
    cur = q;
    p->next = q;
    q->pev = p;
  }
}


// del node
void delNode(node *p){
  if(root == NULL) return ;
  if(p == NULL) return ;


  if(p == root){
    root = p->next;
    p->next->pev = NULL;
    free(p);
    cur = root;
  } else if(p == last){
    last = p->pev;
    p->pev->next = NULL;
    free(p);
    cur = last;
  } else {
    cur = p->pev;
    p->pev->next = p->next;
    p->next->pev = p->pev;
    free(p);
  }
}
// free list
void freelist(node *r){
  if(r == NULL) return;
  node *to_free=  r;
  while (to_free != NULL) {
    r = r ->next;
    free(to_free);
    to_free = r;
  }
}


// reverse list
void reversel(){
  node *z = last;
  last = root;




  while (root != NULL) {
    node *temp;
    temp = root->next;
    root->next = root->pev;
    root->pev = temp;
    root = root->pev;
  }
  root = z;
}
//count dual node List
int countList(node *r){
  node *p = r;
  int c = 0;
  while (p != NULL) {
    c++;
    p = p ->next;
  }
  return c;
}


// insert begin of list
void insertB(VARTYPE val){
  node *p;
  p = makeNode(val);

  if(root == NULL) {
    root = p;
    last = p;
    cur = p;
  } else {
    root->pev = p;
    p->next = root;
    p->pev = NULL;
    root =p;
    cur = p;
  }
}
// insert node to before end

void insertBE(VARTYPE val){
  node *p;
  p = makeNode(val);
  cur = p;
  if(root == NULL) {
    root = p;
    last = p;
  } else {
    p->next = last;
    last ->pev->next = p;
    last ->pev = p;
  }
}

// insert at position

node *insertAtPosition(VARTYPE v,int n){
  if(root == NULL ) {
    printf("\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(root) -1) {
    printf("\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    insertB(v);
  } else if(n == countList(root)){
    insertBE(v);
  } else {
    int c = 0;
    node *p = root->next;
    while (p != NULL) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    insertNb(p,v);
    return cur;
  }
}
// delete at position

node *deleteAtPosition(int n){
  if(root == NULL ) {
    printf("\n\t\t List hasn't create !!\n");
    return NULL;
  }
  if(n < 0 || n > countList(root) -1) {
    printf("\n\t\t Position value invaild !!\n");
    return NULL;
  }
  if(n == 0) {
    delNode(root);
  } else if(n == countList(root)){
    delNode(last);
  } else {
    int c = 0;
    node *p = root->next;
    while (p != NULL) {
      c++;
      if(c == n) break;
      p = p ->next;
    }
    delNode(p);
    return cur;
  }
}

// Devide list

node *devideList(node *r,node *l,int p){
  if(r == NULL) {
    printf("Haven't list insert !!\n");
    return NULL;
  }
  if(p < 0 ||  p > countList(r) -1){
    printf("Positon value invaild !!\n");
    return NULL;
  }
  node *rn = NULL;
  int c = 0;
  node *z = r->next;
  while (z != NULL) {
    c++;
    if(c == p) break;
    z = z ->next;
  }
  rn = z->next;
  l = z;
  z->next = NULL;
  return rn;
}

// Extract list

void *extractList(node *r,node *l,int p,int p2){
  if(r == NULL) {
    printf("Haven't list insert !!\n");
    return NULL;
  }
  if(p < 0 ||  p > countList(r) -1){
    printf("Positon value invaild !!\n");
    return NULL;
  }
  if(p2 < p ||  p2 > countList(r) -1){
    printf("Positon value invaild !!\n");
    return NULL;

  }
  node *rn = r;
  int c = 0;
  node *z = r->next;
  while (z != NULL) {
    c++;
    if(c == p) r = z;
    if(c == p2) l = z;
    z = z ->next;
  }
  r->pev->next  =NULL;
  freelist(rn);
  freelist(l->next);
  l->next = NULL;

}

