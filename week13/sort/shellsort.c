#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define VARTYPE int
#define TIME(BEGIN,END) printf("Time sorting is %.6lf s\n",(double)(END - BEGIN)/CLOCKS_PER_SEC);

void shellsort(VARTYPE *arr,int num);

void printlist(VARTYPE *arr,int num);
VARTYPE * readalist(FILE *s,int num);
int main(int argc, char const *argv[])
{
  clock_t begin,end;
  FILE *fp;
  VARTYPE *arr;
  int i,num;
  if(argc != 3 && argc != 4) printf("%s\n","Wrong Input !!");
  else {
    if(!strcmp(argv[1],"y")) {
      printf("Creating %d Number\n",atoi(argv[2]));
      if((fp = fopen(argv[3],"w+")) == NULL){
        printf("Can't create file\n");
      } else {
        srand(time(NULL));
        fprintf(fp,"%d\n",atoi(argv[2]));
        
        for(i = 0; i < atoi(argv[2]);i++) 
          fprintf(fp,"%d\n",1000-rand()%2000);
        
        rewind(fp);
        fscanf(fp,"%d",&num);
        arr = readalist(fp,num);
        fclose(fp);
        
       printlist(arr,num);	
        begin = clock();
        shellsort(arr,num);
        end = clock();
       printlist(arr,num);
        
        
      }
    } else if(!strcmp(argv[1],"n")) {
      if((fp = fopen(argv[2],"r")) == NULL){
        printf("Can't open file\n");
      } else {
        fscanf(fp,"%d",&num);
        arr = readalist(fp,num);
        fclose(fp);
	
       printlist(arr,num);	
        begin = clock();
        shellsort(arr,num);
        end= clock();
       printlist(arr,num);
      }
    }
    TIME(begin,end);
  }
  return 0;
}



void shellsort(VARTYPE *arr,int num){
  int gap,i,j;
  VARTYPE temp;
  gap = 1;
  while(gap < num) gap = gap*2+1;

  while (gap > 0) {
    for(i = gap;i<num;i++){
      temp = arr[i];
      for(j = i;j>=gap && arr[j - gap]>temp;j-=gap){
        arr[j] = arr[j-gap];
      }
      arr[j] = temp;
    }
    gap= gap/2;
  }
}









void printlist(VARTYPE *arr,int num){
	int i;
	for (i = 0 ; i <num ;i++){
		printf("%d\t",arr[i]);
	}
	printf("\n");
}
VARTYPE * readalist(FILE *s,int num){
	int i;
	VARTYPE *arr;
	arr = (VARTYPE *)malloc(sizeof(VARTYPE)*num);
	for(i = 0; i < num;i++){
		fscanf(s,"%d",&arr[i]);
	}
	return arr;
}
