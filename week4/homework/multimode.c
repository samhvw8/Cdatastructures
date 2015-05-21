#include <Ginz.h>


int BLOCK;
void mytime(void (*cpmode)(FILE*,FILE*,int) ,FILE *fin,FILE *fout,int mode);
void mcopy(FILE *fin,FILE *fout,int MODE);

int main(){

  FILE *fin,*fout;
  char fni[] = "in";
  char fno[] = "out";

  if((fin = fopen(fni,"rb")) == NULL) printf("Can't Open file %s\n",fni);
  else {
    if((fout = fopen(fno,"wb")) == NULL) printf("Can't create file %s\n",fno);
    else {
      while (1) {
        switch(getmenu("Copy by char;Copy by line;Copy By Block",3,1)){          mfflush();
        case 1:mytime(mcopy,fin,fout,1);break;
        case 2:mytime(mcopy,fin,fout,2);break;
        case 3:indent(2);printf("Block size : ");scanf("%d",&BLOCK);          mfflush();
          mytime(mcopy,fin,fout,3);break;
        case 0:fclose(fin);fclose(fout);
          return 0;
        }
      }
    }
  }
}

void mytime(void (*cpmode)(FILE*,FILE*,int) ,FILE *fin,FILE *fout,int mode){
  clock_t t,t1;
  t = clock();
  cpmode(fin,fout,mode);
  t1 = clock();

  indent(2);
  printf("Time for copy by block : %.5lf s",(double)(t1-t)/CLOCKS_PER_SEC);


}

void mcopy(FILE *fin,FILE *fout,int MODE){
  rewind(fin);
  rewind(fout);
  if(MODE == 1){
    do {
      char c;
      c = fgetc(fin);
      fprintf(fout,"%c",c);
    }    while (!feof(fin)) ;
  } else if(MODE == 2){
    do {
      char *s;
      s =  (char *)malloc(sizeof(char)*1000);
      fgets(s,1000,fin);
      fputs(s,fout);
    }    while (!feof(fin)) ;
  } else if(MODE == 3){

    while (!feof(fin)) {
      char *buff;
      buff = (char *)malloc(sizeof(char)*BLOCK);
      int n = fread(buff,sizeof(char),BLOCK,fin);
      fwrite(buff,sizeof(char),n,fout);
      free(buff);
    }
  }
}
