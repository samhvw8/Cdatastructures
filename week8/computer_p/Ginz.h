/**
 * Ginz header 
 */
#ifndef _Ginz_H_
#define _Ginz_H_
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define VALTYPE int
#define INVALID -1
#define MAXOPTION 100
#define TABS 8
#define TAB 2
#define JOINTL "."
#define JOINTR "."
#define ROW '='
#define COLL "||"
#define COLR "||"
/**
 *
  /========== Menu ==========\
  >|  1. Test 1   2. Test 2 |<
  >|  3. Test 3   4. Test 4 |<
  >|  5. Test 5   6. Test 6 |<
  >|  0. Exit               |<
  \==========================/
          Your choice:
 */
// ================================================
//print character  c with (times) 
void repchar(int times,char c);
// max lengthgth in 2 demention string for menu **
int count2da(char arr[][MAXOPTION],int num);
// check string is all number or not
int checkan(char arr[],int length);
// Menu 
int getmenu(const char *a,int o,int EXIT);
// my fflush
void mfflush() ;
// swap interger
void swap(VALTYPE *a , VALTYPE *b);
// sort interger array
void intersort(VALTYPE arr[],VALTYPE n);


float ranfloat(int limdown,int limup);

// standardized name 
void standname(char *str);

int nmstr(char *b,char *a);

#endif 
