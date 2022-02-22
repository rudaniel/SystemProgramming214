#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"

#define MEMSIZE 4096
#define METADATA 9
#define LASTDATA 4 
#define OFFSET 1
static char memory[MEMSIZE];
static int MEMUSED = 0;

typedef struct metadata{
    size_t size;
    bool free;
} metadata;

void *mymalloc(size_t size, char *file, int line){
    printf("Mymalloc called from %s:%d\n", file, line);
    printf("Adding elements \n");
    void *lastBlock =  memory;
    int *last=(int*) lastBlock;
    printf("Beggining lastdata %d\n",*last);
    void *memBlock =  memory+LASTDATA+*last;
    metadata *data;
    int s= MEMSIZE-(METADATA+LASTDATA+*last);
    void *result=NULL;
    if(size>s){
        printf("RETURNED NULL\n");
    }
    else{
        data=(metadata*) memBlock;
        printf("zero \n");
        data->free = 1;
        data->size = size;
        *last=METADATA+size+*last;
        printf("Ending lastdata %d\n",*last);
        result=memory+METADATA+LASTDATA;
        printf("\n    Printing Character Array For 75 Spaces... \n");
        for(int i = 0; i<75; i++){
            printf("        %hhx\n", memory[i]);
        }
        printf("    Finished Printing!\n\n");
        printf("total bits %d\n",*last);
    }
        return result;
} 

void myfree(void *p, char *file, int line){
    printf("Myfree called from %s:%d\n", file, line);
}