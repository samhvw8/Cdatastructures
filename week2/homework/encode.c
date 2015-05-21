#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 1000

void inputstring(char *str,FILE *sf);
void decode(char *input,int k);
void encode(char *input,int k);
int main(int argc, char *argv[])
{
  char str[MAX];
  FILE *f;
  if(argc != 4|| strcmp(argv[2],"e")==0 & strcmp(argv[2],"d")==0 ) printf("Wrong Format.\nFormat: for encode file:\" source-file e coeffition\"\nfor decode file:\" source-file e coeffition\"\n");
  else {
    if((f = fopen(argv[1],"r")) == NULL ) printf("can't read file\n");
    else {
      inputstring(str,f);
      if((f = fopen(argv[1],"w")) == NULL ) printf("can't write file\n");
      else {
       if(strcmp(argv[2],"e")==0) encode(str,atoi(argv[3])); 
       else if(strcmp(argv[2],"d")==0) decode(str,atoi(argv[3]));
      printf("%s\n",str);
      fprintf(f,"%s",str);
      }
    }
  }
  return 0;
}
void inputstring(char *str,FILE *sf){
  int c;
  while ((c = fgetc(sf)) != EOF) {
    *str = c;
    str++;
  }
  *str = '\0';
}
// shift right k value of each character in string 
void encode(char *input,int k){
	while(*input != '\0') {
		if(*input != ' ' && *input != '\n') {
			if((*input + k <= 'z' && *input  +k  >= 'a') ||(*input +k  <= 'Z' && *input  +k  >= 'A' || (*input +k <= '9' && *input  + k >= '0'))) *input+=k;
		
    	else if(*input + k > 'z') *input = 'a' + k - ('z' -*input )-1;
      else if(*input + k > 'Z') *input = 'A' + k - ('Z' -*input )-1;
      else if(*input + k > '9')*input = '0' + k - ('9' -*input )-1;
			
      // else if(*input + k > '9') *input = '0' + k - ('9' -*input )-1;
			// else *input = 'A' + k - ('Z' -*input )-1;
			input++;
		}
		else input++;
	}
}
// shift left k value of each character in string 
void decode(char *input,int k){
  while(*input != '\0' ) {
    if(*input != ' '&& *input != '\n') {
      if((*input - k <= 'z' && *input  - k  >= 'a') ||(*input -k  <= 'Z' && *input  -k  >= 'A' || (*input -k <= '9' && *input  - k >= '0'))) *input-=k;
    else if(*input - k < '0') *input = '9' - k + (*input - '0')+1;
      else if(*input - k < 'a') *input = 'z' - k + (*input - 'a' )+1;
      else if(*input - k < 'A') *input = 'Z' - k + (*input - 'A'  )+1;
      
    
      input++;
    }
    else input++;
  }
}
