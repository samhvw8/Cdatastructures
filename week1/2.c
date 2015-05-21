#include <stdio.h>

int main() {
  int arr[26];
  int c,i;

  for ( i = 0; i < 26; i++) arr[i] = 0;

  printf("\n input : ");

  while((c = getchar()) != EOF)  {
    if ( c < 'Z' && c > 'A') arr[c-'A']++;
    if ( c < 'z' && c > 'A') arr[c-'a']++;
  }

  printf("\n");

  for ( i = 0 ; i <  26 ; i++ ) if(arr[i] != 0) printf("\t%c -  %d\n",i+'A',arr[i]);

  printf("\n");

  return 0;
}
