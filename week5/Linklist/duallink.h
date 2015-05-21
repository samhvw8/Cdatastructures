typedef int VARTYPE;
typedef struct dnode dnode;
struct dnode {
  VARTYPE element;
  dnode *next;
  dnode *pev;
};

dnode *root = NULL;
dnode *last = NULL;




dnode *makedNode(VARTYPE val){
  dnode *new = (dnode *)malloc(sizeof(dnode));
  new->element = val;
  new->next = NULL;
  new->pev =NULL;
  return new;
}


void insertdN(VARTYPE val){
  dnode *p = makedNode(val);

  if(root == NULL){
    root = p;
    last = p;
  } else {
    last->next = p;
    p->pev = last;
    last = p;
  }

}

dnode *finddNode(VARTYPE val){
  dnode *s = root;
  if(root == NULL) return NULL;
  while(s != NULL){
    if(s->element == val) return s;
    s = s->next;
  }
  printf("Not found !!\n");
  return NULL;
}


void insertdNb(dnode *p,VARTYPE val){
  dnode *q = makedNode(val);

  if(root == NULL) {
    insertdN(val);
    free(q);
  } else if(p == root){
    root = q;
    p->pev = q;
    q->next = p;
  }else {
    p->pev->next = q;
    q->pev = p->pev;

    p->pev = q;
    q->next = p;
  }
}

void insertdNa(dnode *p,VARTYPE val){
  dnode *q = makedNode(val);
  if(root ==NULL){
    insertdN(val);
    free(q);
  } else if(p == last){
    last =q;
    p->next = q;
    q->pev = p;

  } else {
    p->next->pev = q;
    q->next = p->next;

    p->next = q;
    q->pev = p;
  }
}



void deldnode(dnode *p){
  if(root == NULL) return ;
  if(p == NULL) return ;


  if(p == root){
    root = p->next;
    p->next->pev = NULL;
    free(p);
  } else if(p == last){
    last = p->pev;
    p->pev->next = NULL;
    free(p);
  } else {
    p->pev->next = p->next;
    p->next->pev = p->pev;
    free(p);
  }
}
