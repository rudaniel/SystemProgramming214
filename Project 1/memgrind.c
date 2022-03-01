#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"



int main(int argc, char**argv){

  int x;
  free(&x);

  int *p = malloc(sizeof(int)*100);
  free(p+1);
  free(p);

  int *w = malloc(sizeof(int)*100);
  int *q = w;
  free(w);
  free(q);  

  char *r = malloc(10);
  char *s = malloc(5);
  free(s);
  char *bestTA = malloc(10);

  char *o = malloc(4097); 

  char *c = malloc(120); 
  free(c);
  char *g = malloc(1); 

  //Below calls malloc fills the data and frees in the middle.
  //Shows no overwritten/lost data.
  char* fill = malloc(10);
  for (int i = 0; i<10; i++){
    fill[i] = 'a';
  }
  char* pp = malloc(5);
  for (int i = 0; i<5; i++){
    pp[i] = 'b';
  }
  char* ppp = malloc(15);
  for (int i = 0; i<15; i++){
    ppp[i] = 'c';
  }
  free(pp);
  char* qq = malloc(3);
  for (int i = 0; i<3; i++){
    qq[i] = 'd';
  }

    return EXIT_SUCCESS;
}