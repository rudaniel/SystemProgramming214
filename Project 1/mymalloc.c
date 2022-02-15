#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE 4096

static char memory[MEMSIZE];
static int MEMUSED = 0;

//creating linked list

//typedef struct node {
//    int data:
//    struct node *next;
//}node;

//struct node *linkedList; //start of the linked list


void *mymalloc(size_t size, char *file, int line){
    printf("Mymalloc called from %s:%d\n", file, line);
    
    size_t trueSize = 0; //memory will be given in 8 bytes.
    if (size % 8 == 0){
        trueSize = size;
    }
    else {
        while(size % 8 != 0){
            size ++;
        }
        trueSize = size;
    }

    printf("The value of trueSize : %zu:\n", trueSize);
    
    if (MEMSIZE - MEMUSED < trueSize) {
         printf("Too large for current free memory. \n");
         return NULL;
    }

    void *memBlock = memory + MEMUSED; //A pointer to the start of free memory.
    MEMUSED += trueSize;

    return memBlock;
} 

void myfree(void *p, char *file, int line){
    printf("Myfree called from %s:%d\n", file, line);
    
}