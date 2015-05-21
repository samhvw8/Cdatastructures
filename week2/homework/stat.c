#include<stdio.h>

void stat(FILE *sf,FILE *df);

int main(int argc, char *argv[])
{
  char fn[] = "sourcestats.txt";
  char fn1[] = "stat.c";
  FILE *fin,*fout;
  
  if((fout= fopen(fn, "w")) == NULL) printf("Can't Create file. \n");
  else {
    if((fin = fopen(fn1, "r")) == NULL) printf("Can't read file. \n");
    else {
      stat(fin,fout);
    }
  }
  fclose(fin);
  fclose(fout);
  return 0;
}
void stat(FILE *sf,FILE *df){
  int c;
  int arr[26];
  for (c = 0; c < 26; c++) {
    arr[c] = 0;
  }

  while ((c = fgetc(sf))!= EOF) {
    if(c <= 'z' && c >= 'a') arr[c-'a']++;
    else if(c <= 'Z' && c >= 'A') arr[c-'A']++;
  }
  for (c = 0; c < 26; c++) {
    fprintf(df,"Character %c : %d\n",c+'a',arr[c]);
  }  
}
