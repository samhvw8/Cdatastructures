

#include "sort.h"


/////// INSERTION SORT

void insersort(void **base,size_t size,int (*compar)(const void *,const void *)){
     size_t i,j;
     for (i = 1; i < size; i++) {

          typeof(base[i]) tmp = base[i];

          for(j = i ; j > 0 && (compar(&base[j-1],&tmp) > 0) ;j--)
               //SWAP(base[j],base[j-1]);
               base[j] = base[j-1];

          base[j] = tmp;
     }
}

////// QUICK SORT
size_t partion(void **base,size_t l,size_t r,size_t pivotI,int (*compar)(const void *,const void *)){
     size_t i,sI;

     typeof(base[pivotI]) pivotV = base[pivotI];

     SWAP(base[pivotI],base[r]);

     sI = l;
     for(i = l; i < r;i++){
          if(compar(&base[i],&pivotV) < 0){
               SWAP(base[i],base[sI]);
               sI++;
          }
     }

     SWAP(base[sI],base[r]);
     return sI;
}

void quicksort(void **base,size_t l,size_t r,int (*compar)(const void *,const void *)){
     if(l > r) return ;
     size_t p, pi = getpivot(base,l,r,compar);

     p = partion(base,l,r,pi,compar);
     if(p == 0) return ;
     quicksort(base,l,p-1,compar);
     quicksort(base,p+1,r,compar);

}

size_t getpivot(void **base,size_t l,size_t r,int (*compar)(const void *,const void *)){
     typeof(base[l]) first,last,medium;

     first = base[l];
     last = base[r];
     medium = base[(l+r)/2];

     if(compar(&first,&last) > 0) {
          if(compar(&first,&medium) > 0) return (l+r)/2;
          else return l;
     }
     else if(compar(&first,&last) < 0) {
          if(compar(&last,&medium) > 0) return (l+r)/2;
          else return r;
     }
     else return (l+r)/2;

}






//// HEAP SORT



void heapsort(void **base,size_t size,int (*compar)(const void *,const void *)){
     size_t i;
     buildHeap(base,size,compar);

     for(i = size-1 ;i>=1 ; i--){
          SWAP(base[0],base[i]);
          heapify(base,i,0,compar);
     }
}
void buildHeap(void **base,size_t size,int (*compar)(const void *,const void *)){
     int i ;
     for(i = size/2;i>=0;i--) heapify(base,size,i,compar);
}

void heapify(void **base,size_t size,size_t loc,int (*compar)(const void *,const void *)){
     size_t left,right,locc;
     loc = loc +1;
     left = 2*loc;
     right = left+1;

     if(left <= size && compar(&base[left-1],&base[loc-1]) > 0) locc = left; else locc = loc;
     if(right <= size && compar(&base[right-1],&base[locc-1]) > 0) locc = right;

     if(locc != loc) {
          SWAP(base[loc-1],base[locc-1]);
          heapify(base,size,locc-1,compar);
     }
}


//// MERGE SORT

// l : left , m mid , r right

void mergesort(void **base,size_t l,size_t r,int (*compar)(const void *,const void *)){

     if(l < r) {
          size_t m = l + (r - l)/2; // same as (l+r)/2 but advoids overflow for large l and r
          mergesort(base,l,m,compar);
          mergesort(base,m+1,r,compar);
          merge(base,l,m,r,compar);
     }
}
void merge(void **base,size_t l,size_t m,size_t r,int (*compar)(const void *,const void *)){

     size_t i,j,k; // index
     size_t n = m - l + 1,
          n2 = r - m;

     void *temp[n], // temp
          *temp2[n2];
     // copy data to temp array
     for(i = 0; i < n ; i++){
          temp[i] = base[l+i];
     }
     for(j = 0; j < n2 ; j++){
          temp2[j] = base[m+1+j];
     }

     i = 0;
     j = 0;
     k = l;
     //
     while(i < n && j < n2){
          if(compar(&temp[i],&temp2[j]) < 0){
               base[k] = temp[i];
               i++;
          } else {
               base[k] = temp2[j];
               j++;
          }
          k++;
     }
     //
     while(i < n){
          base[k] = temp[i];
          i++;
          k++;
     }
     while(j < n2){
          base[k] = temp2[j];
          j++;
          k++;
     }
}

// SHELL SORT

void shellsort(void* *base,size_t size,int (*compar)(const void *,const void *)){
     size_t gap,i,j;
     void * temp;
     gap = 1;
     while(gap < size) gap = gap*2+1;

     while (gap > 0) {
          for(i = gap;i<size;i++){
               temp = base[i];
               for(j = i;j>=gap && compar(&base[j - gap],&temp) > 0;j-=gap){
                    base[j] = base[j-gap];
               }
               base[j] = temp;
          }
          gap= gap/2;
     }
}

//INTROSORT


void introsort(void * *base,size_t size,int (*compar)(const void *,const void *)){
     isort(base,floor(log(size))*2,size,compar);
}

void isort(void * *base,size_t maxdepth,size_t size,int (*compar)(const void *,const void *)){
     size_t p;
     void ** bas; // use bas for saparate array
     if(size<= 1) return;
     else if (maxdepth == 0) heapsort(base,size,compar);
     else{
          size_t pi = getpivot(base,0,size-1,compar);

          bas = base;
          p = partion(base,0,size-1,pi,compar);
          //if(p == 0) return ;
          bas = bas + p + 1;

          isort(base,maxdepth-1,p+1,compar);
          isort(bas,maxdepth-1,size-p-1,compar);
     }
}
