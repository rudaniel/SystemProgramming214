#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE 4096
#define METADATA 5

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
    
    size_t trueSize;
    trueSize=size+METADATA;

    printf("The value of trueSize : %zu:\n", trueSize);
    
    if (MEMSIZE - MEMUSED < trueSize) {
         printf("Too large for current free memory. \n");
         return NULL;
    }
    
    

    void *memBlock = memory + MEMUSED + METADATA; //A pointer to the start of free memory.
    MEMUSED += trueSize;

    return memBlock;
} 

void myfree(void *p, char *file, int line){
    printf("Myfree called from %s:%d\n", file, line);
    
}

void toBytes(int size, char* ptr){
    ptr[0] = (size >> 24) & 0xFF;
    ptr[1] = (size >> 16) & 0xFF;
    ptr[2] = (size >> 8) & 0xFF;
    ptr[3] = size & 0xFF;
}

int toInt(char* size){
    return 0;
}

struct metadata{
    size_t size;
    bool free;
};


