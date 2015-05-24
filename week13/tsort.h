

typedef struct student${
  int no,
    mssv;
  char name[30],
    tel[15];
} student;

void diff(student *a,student *b,int num,int num2);
int rBinSearch(student *L,char *Target,int Lo,int Hi);
int sizefile(FILE *f);
void readff(FILE *f,student **sarr,int *num);
void qsortstudent(student *sarr,int *num);
int cmpDic(const void *a,const void *b);
void printarr(student *sarr,int num);
