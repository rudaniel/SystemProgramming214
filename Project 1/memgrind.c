#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main(int argc, char**argv){

    int *p = malloc(1024);

    free(p);

    return EXIT_SUCCESS;
}