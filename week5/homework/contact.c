#include <stdio.h>
#include <stdlib.h>

typedef struct ${
  char name[40];
  char tel[15];
  char email[30];
} Pcontact;

char *Finput;

void mfflush() {
  int ch;
  while((ch = getchar()) && ch != '\n' && ch != EOF);
}
int num;
void readarr(FILE *fp);
void writearr(FILE *fp);
void editarr(FILE *fp);

int main(int argc,char *argv[]){
  FILE *fp;
  num = atoi(argv[2]);
  Finput = argv[1];

  writearr(fp);
  //readarr(fp);
  return 0;
}

void editarr(FILE *fp){
  int i,irc,no,c;
  Pcontact *pcarr;

  if((fp = fopen(Finput,"r+b")) == NULL) {
    printf("Read file fail \n");
    } else {/*read file*/


    printf("No. Phone contact you want to modifie :");
    scanf("%d",&no);mfflush();

    if(fseek(fp,no*sizeof(Pcontact),SEEK_SET) != 0){
      printf("Fseek failed\n");
    }else{ //Fseek
      pcarr = (Pcontact *)malloc(sizeof(Pcontact));
      irc = fread(pcarr,sizeof(Pcontact),1,fp);

      printf("what you want to mod \n 1.Name \n2.Tel \n3.Email\n");scanf("%d",&c);mfflush();

      if(c == 1){
        printf("New Name :");scanf("%[^\n]",pcarr[0].name);
        mfflush();
      } else if( c == 2){
        printf("New tel :");scanf("%[0123456789]",pcarr[0].tel);
        mfflush();
      } else {
        printf("New email :");scanf("%s",pcarr[0].email);
        mfflush();
      }
      printf("New contact : %s-%s-%s\n",pcarr[0].name,pcarr[0].tel,pcarr[0].email);
      if(fseek(fp,no*sizeof(Pcontact),SEEK_SET) != 0){
        printf("Fseek failed\n");
      }else{
        fwrite(pcarr,sizeof(Pcontact),1,fp);
      }

    }
    fclose(fp);
    free(pcarr);
  }

}




void readarr(FILE *fp){
  int i,irc;
  Pcontact *pcarr;
  if((fp = fopen(Finput,"r+b"))==NULL){
    printf("Can't read file\n");

  } else {
    pcarr = (Pcontact *)malloc(sizeof(Pcontact)*num);
    irc = fread(pcarr,sizeof(Pcontact),num,fp);
    printf("\nAddress : \n");
    for(i = 0; i < num ; i++){
      printf("%s-",pcarr[i].name);
      printf("%s-",pcarr[i].tel);
      printf("%s\n",pcarr[i].email);
    }
    fclose(fp);
    free(pcarr);
  }
}

void writearr(FILE *fp){
  int i,irc;
  Pcontact *pcarr;
  if((fp = fopen(Finput,"w+b")) == NULL){
    printf("Can't create file !!\n");

  } else {
    printf("How many Phone contact you want to create : ");scanf("%d",&num);mfflush();
    pcarr = (Pcontact *)malloc(sizeof(Pcontact)*num);
    for(i = 0;i < num;i++){
      printf("Name :");
      scanf("%[^\n]",pcarr[i].name);mfflush();
      printf("%s's Tel :",pcarr[i].name);
      scanf("%[0123456789]",pcarr[i].tel);mfflush();
      printf("%s's email :",pcarr[i].name);
      scanf("%s",pcarr[i].email);mfflush();

    }

    irc =fwrite(pcarr,sizeof(Pcontact),num,fp);
    printf("frrite return code = %d\n",irc);
    fclose(fp);
    free(pcarr);
  }
}
