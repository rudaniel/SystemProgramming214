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
    void *memBlock =  memory;
    metadata *data = (metadata*) memBlock;
    void *result=NULL;
    if(data->size==0 && data->free==0){
        printf("Fresh List\n");
        if((size+METADATA)>MEMSIZE){
            printf("RETURNED NULL \n");
            return NULL;
        }
        else{
            data->size=size;
            data->free=1;
            result=memory+METADATA;
            int temp=size+METADATA+METADATA;
            if(temp>=MEMSIZE){
                printf("Youre CUCKED \n");
            }
            else{
                void *freeBlock= memory+temp-METADATA;
                metadata *nextFree= (metadata*) memBlock;
                nextFree->free=0;
                nextFree->size=MEMSIZE-temp;
            }
            return result;
        }
    }
    else{
        printf("Not New List\n");
        void *lastPointer=memory+MEMSIZE-OFFSET;
        void *memBlock=memory;
        metadata *data;
        while(memBlock<=lastPointer){
            data = (metadata*) memBlock;
            if(data->free == 0){
                if(data->size>=size){

                }
            }
            memBlock=memBlock+data->size+METADATA;
        }
    }
    return result;
} 

void myfree(void *p, char *file, int line){
    printf("Myfree called from %s:%d\n", file, line);

     void *checker =  memory; 
    //  int *last = (int*) checker; //gets the remainder, it points to the next free position.

    // printf("Remainder value: %d\n", *last);

    // if(*last == 0){
    //     printf("No Elements in Stack\n");
    //     exit(EXIT_FAILURE);
    // }

    void *start =  p-METADATA; 
    void *pointerAddr = p;
    
    
  
    metadata *data = (metadata*) start; //This is the Metadata of the Node we are currently freeing.
    size_t nodeSize = data->size;
   // *last = *last-nodeSize-METADATA;
    printf("Free Data size Before %ld\n", data->size);
    data->free = 0;                     //prayingi can free papi ;)
    printf("Free Data size %ld\n", data->size);

    // char* shifter=(char*) start;
    // int tempamount=MEMSIZE-*last-METADATA-nodeSize;
    // int offset=METADATA+nodeSize;

    char * something = (char*) pointerAddr;

    for (int i =0; i < nodeSize; i++){
        something[i] = '\0';
    }

    // printf("HMMM What do we have here? The start of char array is %d\n", tempamount);
    // for(int i=0; i<tempamount; i++){
    //     (start+i)=*(start+i+offset);
    // }



  //  printf("Char Test: %c\n", *something);

     for(int i = 0; i<100; i++){
            printf("        %hhx\n", memory[i]);
        }
        printf("    Finished Printing!\n\n");

}