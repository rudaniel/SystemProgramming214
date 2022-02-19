#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"

typedef struct metadata{
   //struct Metadata *next;
    size_t size;
    bool free;
} metadata;

int main(int argc, char**argv){

  metadata* p= malloc(10);
printf("We are in main function. The size is %ld and the free is %d.", p->size,p->free);




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