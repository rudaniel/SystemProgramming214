#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mymalloc.h"

#define MEMSIZE 4096
#define METADATA 9

static char memory[MEMSIZE];
static int MEMUSED = 0;

typedef struct metadata{
   //struct Metadata *next;
    size_t size;
    bool free;
} metadata;

//creating linked list

//typedef struct node {
//    int data:
//    struct node *next;
//}node;

//struct node *linkedList; //start of the linked list


void *mymalloc(size_t size, char *file, int line){
    printf("Mymalloc called from %s:%d\n", file, line);
    
    size_t trueSize = 0;
   // trueSize=size+METADATA;
//    for(int i = 0; i<100; i++){
//        //memory[i]=5;
//         printf(" %hhx\n", memory[i]);
//     }
    printf("Adding elements \n");
    void *memBlock =  memory;
   metadata *data;
    for(int i=0; i<400;i++){
        data=(metadata*) memBlock;
    if(data->free==0&& data->size==0){
        data->free = 1;
        data->size = size;
        break;
    }
        memBlock=memBlock+METADATA+data->size;
    }
    printf("adress of memory %p\n", memory);
        printf("adress of memory[0] %p\n", &memory[0]);

    printf("adress of memoryadd %p\n", memBlock);


//    void *memBlock2 =  memory+METADATA+data->size;
//    metadata *data2= (metadata*) memBlock2;
//    data2->free = 1;
//    data2->size = 500;
   
metadata* p=memBlock;
printf("We are in malloc function. The size is %ld and the free is %d.\n", p->size,p->free);
  // memBlock= &data;

  // struct metadata yeet= *memBlock;
   //printf("Size of yeet: %ld\n", yeet.size);
  // struct metadata first= (*struct metadata) *memBlock;
  // printf("Metadata Size is : %ld free: %d\n", first.size, first.free);
for(int i = 0; i<100; i++){
        printf(" %hhx\n", memory[i]);
    }
   printf("Size of struct: %ld\n", sizeof(*data));

         //the memory array is empty
        //memory[0] = (char *) (sizeof(data));
    
  


 // while (memory != 0){
  //    trueSize ++;
 // }

    // printf("The value of trueSize : %zu:\n", trueSize);
    
    // if (MEMSIZE - MEMUSED < trueSize) {
    //      printf("Too large for current free memory. \n");
    //      return NULL;
    // }
    
    

    // void *memBlock = memory + MEMUSED + METADATA; //A pointer to the start of free memory.
    // MEMUSED += trueSize;

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




