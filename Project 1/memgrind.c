#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"



int main(int argc, char**argv){

  char* p= malloc(10);

  for (int i = 0; i<10; i++){
    p[i] = 'a';
  }
    //free(p);
  char* pp= malloc(15);

  for (int i = 0; i<15; i++){
    pp[i] = 'b';
  }
 free(p);
 // int *q =malloc(0);
char* pdfp= malloc(20);
 for (int i = 0; i<20; i++){
    pdfp[i] = 'c';
  }
  char* pdsdffp= malloc(10);


 // int* q= malloc(10);


//int* pp= malloc(25);



//int* ppp= malloc(5);

//int* breaker= malloc(4021);



  //   int *p = malloc(10);

  //   for(int i = 0; i <10; i++){
  //       p[i] = i;
  //   }

  //   int *q = malloc(10);
    
  // //  for(int i = 0; i <1024; i++){
  // //        printf( "%d: \n", p[i]);
  // //  }
  //   free(p);
  //   // gcc memgrind.c mymalloc.c -o test
  //   // ./filename
    return EXIT_SUCCESS;
}