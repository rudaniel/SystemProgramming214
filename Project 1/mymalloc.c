#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

#define MEMSIZE 4096

static char memory[MEMSIZE];
static int MEMUSED = 0;

//creating linked list

typedef struct Node {
    void  *data;      //generic linked list
    int free;         //used to known if that linked list is free or not.
    struct Node *next;
};

void insertList (void **data){
    struct NODE *list = (struct Node*) malloc(sizeof(struct Node)); //Creates of type node and calls mymalloc for the space.

    list->data = ;
    list->free = 0;

}

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