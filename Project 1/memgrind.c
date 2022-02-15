#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char**argv){

  





    int *p = malloc(100);

    for(int i = 0; i <100; i++){
        p[i] = i;
    }
    
    for(int i = 0; i <100; i++){
          printf( "%d: \n", p[i]);
    }

    free(p);
    // gcc memgrind.c mymalloc.c -o test
    // ./filename
    return EXIT_SUCCESS;
}