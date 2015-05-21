#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char **argv){
  if ( argc != 3 ) printf("Input Wrong !! input again\n");
  else {
  printf("\n Dien tich hinh chu nhat %.1fx%.1f : %.1f",atof(argv[1]),atof(argv[2]),atof(argv[1])*atof(argv[2]));
  printf("\n Chu vi hinh chu nhat %.1fx%.1f : %.1f\n\n",atof(argv[1]),atof(argv[2]),2*(atof(argv[1])+atof(argv[2])));
  }
  return 0;
}
