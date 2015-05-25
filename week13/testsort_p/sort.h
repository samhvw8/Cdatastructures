/*
  Collection of sort function sort array of pointer which pointer to some kind of type
  */

#ifndef _SORT_GINZ_H_
#define _SORT_GINZ_H_


#ifndef SWAP
#define SWAP(x , y) do { typeof(x) TEMP = (x); (x) = (y) ; (y) =TEMP;} while (0);
#endif


#include <stdio.h>
#include <stdlib.h>
#include <math.h> // for introsort

// insertion sort

void insersort(void **base,size_t size,int (*compar)(const void *,const void *));

//quick sort

void quicksort(void **base,size_t l,size_t r,int (*compar)(const void *,const void *));
size_t partion(void **base,size_t l,size_t r,size_t pivotI,int (*compar)(const void *,const void *));
size_t getpivot(void **base,size_t l,size_t r,int (*compar)(const void *,const void *));
// heap sort

void heapsort(void **base,size_t size,int (*compar)(const void *,const void *));
void buildHeap(void **base,size_t size,int (*compar)(const void *,const void *));
void heapify(void **base,size_t size,size_t loc,int (*compar)(const void *,const void *));


// MERGE SORT

void merge(void **base,size_t l,size_t m,size_t r,int (*compar)(const void *,const void *));
void mergesort(void **base,size_t l,size_t r,int (*compar)(const void *,const void *));

// SHELL SORT

void shellsort(void* *base,size_t size,int (*compar)(const void *,const void *));

// INTRO SORT

void introsort(void * *base,size_t size,int (*compar)(const void *,const void *));
void isort(void * *base,size_t maxdepth,size_t size,int (*compar)(const void *,const void *));

#endif
