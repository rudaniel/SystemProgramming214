#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char**argv){

    int *p = malloc(1024);

    free(p);
    // gcc memgrind.c mymalloc.c -o filename
    // ./filename
    return EXIT_SUCCESS;
}