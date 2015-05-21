#include <stdio.h>
#include <math.h>
#define MAX 10


int input(int *arr);
double av(int *arr,int len);
void medias(int *arr,int len);


int main () {
  int len,arr[MAX];
  len = input(arr);
  medias(arr,len);
  
  return 0;

}

void medias(int *arr,int len){
  double ava,dis,dism;
  int i;
  ava = av(arr,len);
  
  dis = 0;
  dism = fabs(ava - arr[0]);

  for (i = 1; i < len ; i++) {
    dis = fabs(ava - arr[i]);
    if( dis < dism )  dism = dis;
  }
  printf("\n");
  for ( i = 0 ; i < len ; i++) {
    if(dism ==  fabs(ava - arr[i])) printf("%d\t",arr[i]);
  }
  printf("\n");
}
double av(int *arr,int len){
  int sum,i;sum = 0;
  for( i = 0;i < len ;i++) sum += arr[i];
  
  return sum/len;
}
int input(int *arr){
  int i,n;
  printf("\n how many number you want to input :");scanf("%d",&n);
  printf("\n Input array : ");
  for (i = 0; i <n ; i++) scanf("%d",&arr[i]);

  return n;
}
