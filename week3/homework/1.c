
#include <Ginz.h>
typedef struct $student {
  int no;
  long stin;
  char fullname[30];
  char phone[15];
  int mark;
} student;

int n;
void ptof(student *arr,FILE *fout);
student * inff(FILE *fin);
int countlinef(FILE *fin);
int main(int argc, char *argv[])
{
  int i;
  student *arr;
  FILE *fin,*fout;
  if(argc != 2) printf("Wrong output !!\n");
  else {
    if((fin = fopen(argv[1],"r"))==NULL) printf("Can't read nfile\n");
    else if((fout = fopen("bangdiem.txt","w"))==NULL) printf("Can't write file\n");
    else {
      n = countlinef(fin);
      if((fin = fopen(argv[1],"r"))==NULL) printf("Can't read nfile\n");
      else {
        arr = inff(fin);
        ptof(arr,fout);
      }

    }
    fclose(fin);
    fclose(fout);
  }

  return 0;
}
void ptof(student *arr,FILE *fout){
  int i;
  for (i = 0; i < n; i++) {
    printf("Diem cua sinh vien %s : ",arr->fullname);
    scanf("%d",&arr->mark);
    arr++;
  }
  arr = arr-n;
  for (i = 0; i < n; i++) {
    fprintf(fout,"%-3d %-ld %-30s %s %d\n",arr[i].no,arr[i].stin,arr[i].fullname,arr[i].phone,arr[i].mark);
    printf("%-3d %-ld %-30s %s %d\n",arr[i].no,arr[i].stin,arr[i].fullname,arr[i].phone,arr[i].mark);
  }

}

student * inff(FILE *fin){
  student *arr;
  int i;
  arr = (student *)malloc(sizeof(student) * n);
  for(i = 0; i < n ;i++) {
    fscanf(fin,"%d %ld%[^0-9]%s",&arr->no,&arr->stin,arr->fullname,arr->phone);
    arr++;
  }
  arr = arr - n;
  return arr;
}
int countlinef(FILE *fin){
  char s[1000];
  int c = 0;
  while (fgets(s,1000,fin)!=NULL) {
    c++;
  }
  fclose(fin);

  return c;
}
