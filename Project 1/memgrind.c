#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char**argv){

  





    int *p = malloc(10);

    for(int i = 0; i <10; i++){
        p[i] = i;
    }

    int *q = malloc(10);
    
  //  for(int i = 0; i <1024; i++){
  //        printf( "%d: \n", p[i]);
  //  }
    free(p);
    // gcc memgrind.c mymalloc.c -o test
    // ./filename
    return EXIT_SUCCESS;
}