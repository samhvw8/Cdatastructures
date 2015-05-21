#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct ${
  int size;
  char author[30];
  char date[12];
} head;


int fsize(FILE *f);

void Chead(FILE *f);//create header
void Rhead(FILE *f);//read header
void Rmhead(FILE *f, char *n); // remove header

void mcopy(FILE *scf,FILE *d);

int main(int argc, char *argv[])
{
  FILE *fin;
  if(argc != 3) printf("Wrong format !! \n format : ./header <option> <input file>\n <option> : '-c' create header ; '-r' read header ; '-d' remove header\n");
  else {
    if((fin  = fopen(argv[2],"r+b")) == NULL) printf("Can't read file %s !!\n",argv[2]);
    else {
      switch(argv[1][1])
        {
        case 'c':Chead(fin);fclose(fin);break;
        case 'r':Rhead(fin);fclose(fin);break;
        case 'd':Rmhead(fin,argv[2]);break;
        default:printf("Wrong option \n<option> : '-c' create header ; '-r' read header; '-d' remove header\n");fclose(fin);break;
        }

    }
  }

  return 0;
}

// copy
void mcopy(FILE *scf,FILE *d){
  int BLOCK = 100;
  char c;
  int prev = ftell(scf);
  while (!feof(scf)) {
    char *buff;
    buff = (char *)malloc(sizeof(char)*BLOCK);
    int n = fread(buff,sizeof(char),BLOCK,scf);
    fwrite(buff,sizeof(char),n,d);
    free(buff);
  }
  fseek(scf,prev,SEEK_SET);
}


//create header
void Chead(FILE *f){
  char beginh[] = "====Header====";
  FILE *tmpf;
  head *Fhead;
  Fhead = (head *)malloc(sizeof(head));
  tmpf = tmpfile();
  mcopy(f,tmpf);

  rewind(tmpf);
  Fhead->size = fsize(f);

  printf("What is author name : ");scanf("%[^\n]",Fhead->author);
  printf("What is date :");scanf("%s",Fhead->date);

  fwrite(beginh,sizeof(char),sizeof(beginh),f);
  fwrite(Fhead,sizeof(head),1,f);
  free(Fhead);
  mcopy(tmpf,f);
  fclose(tmpf);


}

//read header
void Rhead(FILE *f){
  char beginh[] = "====Header====";
  char buff[15];
  head *Fhead;
  Fhead = (head *)malloc(sizeof(head));

  fread(buff,sizeof(char),sizeof(beginh),f);

  if(!strcmp(buff,beginh)) {
    fread(Fhead,sizeof(head),1,f);
    printf("Size file : %d bytes\n",Fhead->size);
    printf("Author : %s\n",Fhead->author);
    printf("Date : %s\n",Fhead->date);
  } else {
    printf("File doesn't have header \n");
  }
  free(Fhead);

}

//remove header
void Rmhead(FILE *f, char *n){
  char beginh[] = "====Header====";
  char buff[15];
  FILE *tmpf;
  head *Fhead;

  fread(buff,sizeof(char),sizeof(beginh),f);

  if(!strcmp(buff,beginh)) {
    fseek(f,sizeof(head),SEEK_CUR);
    if((tmpf = fopen("asdasdasd","w+b"))  != NULL)
      mcopy(f,tmpf);

    fclose(f);
    fclose(tmpf);
    remove(n);

    rename("asdasdasd",n);

  } else {
    printf("File doesn't have header \n");
  }

}


int fsize(FILE *f){
  int e = 0;
  int prev = ftell(f);
  fseek(f,e,SEEK_END);
  int size = ftell(f);
  fseek(f,prev,SEEK_SET);
  return size;
}
