#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE 4096

static char memory[MEMSIZE];

void *mymalloc(size_t size, char *file, int line){
    printf("Mymalloc called from %s:%d\n", file, line);

    return NULL;
} 

void myfree(void *p, char *file, int line){
    printf("Myfree called from %s:%d\n", file, line);
    
}