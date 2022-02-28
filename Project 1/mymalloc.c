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
    printf("Input Size %ld\n", size);
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
            data->free=1;
            result=memory+METADATA;
            int temp=size+METADATA+METADATA;
            if(temp>MEMSIZE){
                data->size=MEMSIZE-METADATA;
                printf("Youre CUCKED \n");
            }
            else{
                printf("size: %ld\n",size);
                data->size=size;
                void *freeBlock= memory+temp-METADATA;
                metadata *nextFree= (metadata*) freeBlock;
                nextFree->free=0;
                nextFree->size=MEMSIZE-temp;
                printf("nextsize: %ld\n",nextFree->size);
                printf("datasize1: %ld\n",data->size);
            }
            printf("datasize2: %ld\n",data->size);

             for(int i = 0; i<100; i++){
            printf("        %hhx\n", memory[i]);
             }
            printf("    Finished Printing!\n\n");

            return result;
        }
    }
    else{
        printf("Not New List\n");
        void *lastPointer=memory+MEMSIZE-OFFSET;
        void *memBlock=memory;
        metadata *data;
        int tracker = 0;
        while(memBlock<=lastPointer){
            data = (metadata*) memBlock;
            tracker ++;
            printf("Track: %d\n",tracker);
            if(data->free == 0){
                printf("Inside If  Statement \n");
                 printf("Inside if data.size: %ld\n",data->size);
                if(data->size>=size){
                    result=memBlock+METADATA;
                     printf("Inside if size: %ld\n",size);
                    int temp=size+METADATA;
                    printf("Inside if temp: %d\n",temp);
                    data->free=1;
                    if(temp>data->size){
                        printf("Youre CUCKED \n");
                    }
                    else{
                        printf("size: %ld\n",size);
                        void *freeBlock= memBlock+temp;
                        metadata *nextFree= (metadata*) freeBlock;
                        nextFree->free=0;
                        nextFree->size= data->size-temp;
                        data->size=size;
                        printf("nextsize: %ld\n",nextFree->size);
                        printf("datasize1: %ld\n",data->size);
                    }
                    printf("datasize2: %ld\n",data->size);
                  
                    break;
                }
            }
            memBlock=memBlock+data->size+METADATA;
        }

         for(int i = 0; i<100; i++){
            printf("        %hhx\n", memory[i]);
        }
            printf("    Finished Printing!\n\n");

    }
    return result;
} 

void myfree(void *p, char *file, int line){
    printf("Myfree called from %s:%d\n", file, line);
    void *checker =  memory; 
    void *start =  p-METADATA; 
    void *pointerAddr = p;
    metadata *data = (metadata*) start; //This is the Metadata of the Node we are currently freeing.
    size_t nodeSize = data->size;
    printf("Free Data size Before %ld\n", data->size);
    data->free = 0;
    printf("Free Data size %ld\n", data->size);
    char * something = (char*) pointerAddr;
    for (int i =0; i < nodeSize; i++){
        something[i] = '\0';
    }
    for(int i = 0; i<100; i++){
        printf("        %hhx\n", memory[i]);
    }
    printf("    Finished Printing!\n\n");

    //merging free blocks
    void *lastPointer=memory+MEMSIZE-OFFSET;
    void *memBlock=memory;
    metadata *prev=memBlock;
    memBlock=memBlock+prev->size+METADATA;
    metadata *node;
    int tracker = 0;
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