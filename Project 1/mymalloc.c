#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"

#define MEMSIZE 4096
#define METADATA 9
#define LASTDATA 4 
#define OFFSET 1
static char memory[MEMSIZE];

typedef struct metadata{
    size_t size;
    bool free;
} metadata;

void *mymalloc(size_t size, char *file, int line){
    //printf("Mymalloc called from %s:%d\n", file, line);
    void *memBlock =  memory;
    metadata *data = (metadata*) memBlock;
    void *result=NULL;
    if(data->size==0 && data->free==0){
        if((size+METADATA)>MEMSIZE){
            return NULL;
        }
        else{
            data->free=1;
            result=memory+METADATA;
            int temp=size+METADATA+METADATA;
            if(temp>MEMSIZE){
                data->size=MEMSIZE-METADATA;
            }
            else{
                data->size=size;
                void *freeBlock= memory+temp-METADATA;
                metadata *nextFree= (metadata*) freeBlock;
                nextFree->free=0;
                nextFree->size=MEMSIZE-temp;
             }
            return result;
        }
    }
    else{
        void *lastPointer=memory+MEMSIZE-OFFSET;
        void *memBlock=memory;
        metadata *data;
        while(memBlock<=lastPointer){
            data = (metadata*) memBlock;
            if(data->free == 0){
                if(data->size>=size){
                    result=memBlock+METADATA;
                    int temp=size+METADATA;
                    data->free=1;
                    if(temp>data->size){

                    }
                    else{
                        void *freeBlock= memBlock+temp;
                        metadata *nextFree= (metadata*) freeBlock;
                        nextFree->free=0;
                        nextFree->size= data->size-temp;
                        data->size=size;
                    }
                    break;
                }
            }
            memBlock=memBlock+data->size+METADATA;
        }
    }
    return result;
} 

void myfree(void *p, char *file, int line){
    //printf("Myfree called from %s:%d\n", file, line);
    if(p==NULL){
        printf("Pointer cannot be NULL. ");
        printf("At " __FILE__ ":%d\n", __LINE__);
        return;
    }
    void *lastPointer=memory+MEMSIZE-OFFSET;
    void *checker =  memory; 
    if(p<checker||p>lastPointer){
        printf("Address was not obtained from Malloc. ");
        printf("At " __FILE__ ":%d\n", __LINE__);
        //exit(EXIT_FAILURE);
        return;
    }
    void *start =  p-METADATA; 
    void *pointerAddr = p;
    metadata *data = (metadata*) start; //This is the Metadata of the Node we are currently freeing.
    if((data->size<0 || data->size > (MEMSIZE-METADATA))||(data->free!=0 && data->free!=1)){
        printf("Invalid Memory Address. ");
        printf("At " __FILE__ ":%d\n", __LINE__);
        //exit(EXIT_FAILURE);
        return;
    }
    if(data->free==0){
        printf("Address has been previously freed. ");
        printf("At " __FILE__ ":%d\n", __LINE__);
        //exit(EXIT_FAILURE);
        return;
    }
    size_t nodeSize = data->size;
    data->free = 0;
    char * something = (char*) pointerAddr;
    for (int i =0; i < nodeSize; i++){
        something[i] = '\0';
    }

    //merging free blocks
    void *memBlock=memory;
    metadata *prev=memBlock;
    memBlock=memBlock+prev->size+METADATA;
    metadata *node;
    while(memBlock<=lastPointer){
        node = (metadata*) memBlock;
        if(prev->free==0 && node->free==0){
            prev->size=prev->size+node->size+METADATA;
            memBlock=memBlock+node->size+METADATA;
            node->size=0;
        }
        else{
            prev=(metadata*) memBlock;
            memBlock=memBlock+node->size+METADATA;
        }
    }
}